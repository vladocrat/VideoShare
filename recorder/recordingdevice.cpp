#include "recordingdevice.h"

#include <QDebug>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

namespace recorder
{

struct RecordingDevice::impl_t
{
    AVFormatContext* formatCtx { nullptr };
    AVCodecContext* codecCtx { nullptr };
    SwsContext* swsCtx { nullptr };

    impl_t(AVFormatContext* formatCtx, AVCodecContext* codecCtx, SwsContext* swsCtx)
        : formatCtx{formatCtx}
        , codecCtx{codecCtx}
        , swsCtx{swsCtx}
    {

    }

    ~impl_t()
    {
        avformat_free_context(formatCtx);
        avcodec_free_context(&codecCtx);
        sws_freeContext(swsCtx);
    }
};

AVFormatContext* const RecordingDevice::formatCtx() const
{
    return impl().formatCtx;
}

AVCodecContext* const RecordingDevice::codecCtx() const
{
    return impl().codecCtx;
}

SwsContext* const RecordingDevice::swsCtx() const
{
    return impl().swsCtx;
}

RecordingDevice::RecordingDevice(AVFormatContext* formatCtx, AVCodecContext* codecCtx, SwsContext* swsCtx)
{
    createImpl(formatCtx, codecCtx, swsCtx);
    qDebug() << Q_FUNC_INFO;
}

RecordingDevice::~RecordingDevice()
{
    qDebug() << Q_FUNC_INFO;
}

}
