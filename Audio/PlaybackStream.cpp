#include <pulse/stream.h>
#include <QDebug>
#include "PlaybackStream.h"
#include "BufferAttributes.h"
#include "PulseAudioHandler.h"
#include "MainLoopLocker.h"
#include "Settings/Settings.h"
#include "Network/NetSocket.h"


using namespace pulse;


PlaybackStream::PlaybackStream(ContextPtr ctx, SampleSpecification* sample,
                BufferAttributes* buffAttr, ChannelMapPtr map, NetSocket* sock)
    : BasicStream(ctx, sample, buffAttr, map, sock)
    , m_mutex()
    , m_queueBuffer()
    , m_kit(&m_queueBuffer, &m_mutex)
{

    MainLoopLocker lock(PulseAudioHandler::instance().mainLoop());

    if (Settings::instance().value(Settings::usePlaybackAsyncAccessModel).toBool())
        pa_stream_set_write_callback(stream(), PlaybackStream::writeAsyncAccess, static_cast<void*>(&m_kit));
    else
        pa_stream_set_write_callback(stream(), nullptr, NullData);

    if (pa_stream_connect_playback(stream(), BasicDevice, bufferAttributes()->get(),
                                   PlaybStreamFlags, nullptr, nullptr) != 0)
        qDebug() << "Recording Stream is not connected";
    while (true)
    {
        int ret = pa_stream_get_state(stream());
        if (ret == PA_STREAM_READY)
            break;
        else if (ret == PA_STREAM_FAILED)
        {
            qDebug() << "PA_STREAM_FAILED";
            return;
        }
        pa_threaded_mainloop_wait(PulseAudioHandler::instance().mainLoop());
    }
}

PlaybackStream::~PlaybackStream()
{

}

void PlaybackStream::resume()
{
    pa_stream_cork(stream(), 0, 0, PulseAudioHandler::instance().mainLoop());
}

void PlaybackStream::pause()
{
    pa_stream_cork(stream(), 1, 0, PulseAudioHandler::instance().mainLoop());
}

void PlaybackStream::writePolledAccess()
{
    static const int16_t fragsize = pulse::Settings::instance().value(pulse::Settings::bufferFragSize).toInt();

    QByteArray buffer(fragsize, 0);
    size_t len  = socket()->receive(buffer.data(), fragsize);
    if (len <= 0)
        return;

    size_t requestedBytes = pa_stream_writable_size(stream());
    if (len > requestedBytes)  len = requestedBytes;

    uint8_t* b;
    pa_stream_begin_write(stream(), reinterpret_cast<void**>(&b), &len);

    for (size_t i = 0; i < len; ++i) b[i] = (buffer.data())[i];

    pa_stream_write(stream(), b, len, nullptr, 0, PA_SEEK_RELATIVE);
}

void PlaybackStream::receiveData()
{
    static const int16_t fragsize = pulse::Settings::instance().value(pulse::Settings::bufferFragSize).toInt();
    QByteArray buffer(fragsize, 0);

    int len  = socket()->receive(buffer.data(), buffer.size());

    if (len < 0)
        return;

    QMutexLocker lock(&m_mutex);
    for (int i = 0; i < len; ++i) m_queueBuffer.push_back((buffer.data())[i]);
}

void PlaybackStream::writeAsyncAccess(StreamPtr stream, size_t requestedBytes, void* kit)
{
    AsyncKit* params = static_cast<AsyncKit*>(kit);

    QQueue<uint8_t>* queueBuffer = params->first;
    QMutex* mutex = params->second;

    QMutexLocker lock(mutex);

    if (queueBuffer->empty())
    {
        pa_stream_flush(stream,nullptr,nullptr);
        return;
    }

    uint8_t* b;
    size_t bytesToFill = queueBuffer->size();
    if (bytesToFill > requestedBytes)  bytesToFill = requestedBytes;
    pa_stream_begin_write(stream, reinterpret_cast<void**>(&b), &bytesToFill);

    for (size_t i = 0; i < bytesToFill; ++i)
    {
        b[i] = queueBuffer->front();
        queueBuffer->pop_front();
    }

    lock.unlock();

    pa_stream_write(stream, b, bytesToFill, nullptr, 0, PA_SEEK_RELATIVE);
}
