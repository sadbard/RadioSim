// ----------------------------------  def.h   ------------------------------------------------------
/* Playback and record buffer metrics
typedef struct pa_buffer_attr {

    uint32_t maxlength;
        ������������ ����� ������ � ������. ��������� ����� ��������
    � (uint32_t) -1 �������������� ��� �� ������������� ��������, ���������������
    ��������, ������� �������������. � ������� ��������� ��������������� � ������
    ��������� �� ������ �������� ���������� ��� ����� ������� ��������, ��������,
    ������ � ������ PA_STREAM_ADJUST_LATENCY. ���� �� �������� ���, �� ������������,
    ��� �������� �� �������� ���������� ��� ������� �������� ������������� ��������
    �� ���� ���������� ����������(?), ���� �������� ���� ���, � ������� ������ �����
    ������� ����������.

    uint32_t tlength;
        ������ ��� ���������������: ������� ����� ������. ������ �������� �������������,
    ��� �� ������� ���� tlength ���� ������ �������� � ������ ��������������� ��� �������
    ������ �� ������� �������. ������������� ���������� ��� ����� �������� (uint32_t) -1,
    ������� �������������� ��� �������� �� ��������, ������� ������ ������� ��������.
    ������ �� ��������� ��� �������� ����� ����� ����-�� ����� 2s, �.�. ��� ����������,
    ������������� ������ ���������� � ��������, ��� �������� ������ ���� ����������� ��
    ������������ ��������, � ������� ����� ���������� ����������. ���� ��������
    PA_STREAM_ADJUST_LATENCY �� ����������, ��� �������� ����� ������ ������ �� ������
    ������ ��������������� ��� ������� ������. ����� ������ �������� PA_STREAM_ADJUST_LATENCY,
    ����� �������� ��������� ���� ������ ������ ��������������� ������������� �� ��� ��������.
    ���������� PA_STREAM_ADJUST_LATENCY, ���� �� �������������� � ����������� ����� ��������.
    �� �������������� ���, ���� �� �������������� � ��������� ������� ������ ���������������
    �� ������� ������� ��� ������� ������.

    uint32_t prebuf;
        ������ ���������������: ��������������� �����������. ������ �� ������ ���������������
    �� ��� ���, ���� � ������ �� ����� �������� �� ������� ���� ���� ��������������� ������.
    ������������� ���������� ��� ����� �������� (uint32_t) -1, ������� �������������� ��� ���
    �� ���������, ��� � tlength, ����� �� ��� �� ����. ��������������� �������� 0, ����� ��������
    ������ ���������� ��������/���������� ������. ��� ��������, ��� ��������������� �� �����������
    ��� ������������� ������� � ��������������� �� �������� �������������. ������ �����
    pa_stream_cork() ������ ���� ������ ����. ���� �� ���������� ��� �������� ������ 0, �� �����
    ������ ���������� PA_STREAM_START_�ORKED.

    uint32_t minreq;
        ������ ���������������: ����������� ������. ������ �� ����������� � ������� ������ minreq ����,
    ������ ����� �������, ���� ����� �� ����������� ����������, ����� ��������� ������ ������ �����.
    ������������� ���������� ��� ����� �������� (uint32_t) -1, ������� �������������� ��� �������� ��
    ��������, ������� ������ ������� ��������. ��� �������� ������ ���� ����������� �� ��������,
    ������� ���� PulseAudio ���������� ������� ��� ����������� ������ �� ������ ��������������� ���
    ������� ������ � ����� ����������� ���������������.

    uint32_t fragsize;
        ������ ������: ������ ���������. ������ ���������� ������ ������� �������� � fragsize ����.
    ������� �������� ��������� ��������������� � ������� ���������� � ��������� �����������, ��
    ��������� ��������� ������� �� ����������. ������������� ���������� ��� ����� �������� (uint32_t)-1,
    ������� �������������� ��� �������� �� ��������, ������� ������ ������� ��������. ������ ��
    ��������� ��� �������� ����� ����� ����-�� ����� 2s, �.�. ��� ����������, ������������� ������
    ���������� � ��������, ��� �������� ������ ���� ����������� �� ������������ ��������, � �������
    ����� ���������� ����������. ���� ������ �������� PA_STREAM_ADJUST_LATENCY, ����� ��������
    ��������� ����� ��������������� � ������������ � ���� ���������. ���� �� �� ����������, ��������
    ��������� �������� ������������.

} pa_buffer_attr;   */

// ----------------------------------  def.h/end    ---------------------------------------------------


/* ����������� ������ ������ �� ������ (��� ��������������� �������). ��� ������� ����� ������������ ���
����������� ���������� ����� ������ ��� ��������������� ("������� �����������"). ������������� ��������
��� ������� ����� ������ ������� pa_stream_write(). ��������� ����� ��������� � ������ ���������� ������,
������� �� ������ ��������. �� ����������� ��� �������� ����� ��������� ���������, ���� �� ������
��������� ������ ��� ������, � ������������ ���������� ������, ������� �� ������ ��������. \a *nbytes
����� ���� ������ ��� ����� �� �� ��������, ������� �� ��������. �� ������ ����� ����������� ������������
��� ������. ������ � ������ �� ��������� ������������� �������� \a *nbytes ����������.
 ������ � ������, ������������ ����� ���������� pa_stream_write() ��� pa_stream_cancel_write(),
��������������. ��� ������ ���������� ���������������� ������ \a *nbytes, ��� �������� ����� �������������
��� *data, ��� � *nbytes. ���� �� ��������� (size_t) -1 � *nbytes ��� ������, ������ ������ ����� ������
������������� (��� ������������� ������). ����� ��������� ����� ������ � ������������ ������� ������
�������� pa_stream_write() � ������� ������ \a ��� ������ � ���� ������� ������ � ��������� \a nbytes,
������� ������ ��� ����� ����, ��� ���� ���������� ���� ��������, ����� ���������� ��������� ������.
����� pa_stream_write() ������ ��������� "������" �� pa_stream_begin_write(). �� ������������� ���������
�������������� ���������� ������� ����� ������ pa_stream_begin_write() � �� ������ pa_stream_write().
���� �� ������ �������� ����� ��������� pa_stream_begin_write() ��� ������ pa_stream_write(), �����������
pa_stream_cancel_write(). ������� ����� pa_stream_begin_write() ��� ������ pa_stream_write() ���
pa_stream_cancel_write() ������ ����� ����� �� �������� \a data pointer � \anbytes. ��� ������� �����
�������������� ��� ����������� ���������� ����� ������ ��� ��������������� (�������� �����������).
������������� �������� ��� ������� ����� ������ ������� pa_stream_write(). ��������� ����� ���������
� ������ ���������� ������, ������� �� ������ ��������. �� ����������� ��� �������� ����� ���������
���������, ���� �� ������ ��������� ������ ��� ������, � ������������ ���������� ������, ������� ��
������ ��������. \a *nbytes ����� ���� ������ ��� ����� �� �� ��������, ������� �� ��������. �� ������
����� ����������� ������������ ��� ������.
*/


