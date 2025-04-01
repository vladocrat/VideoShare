#include "frameworker.h"
#include "libavutil/imgutils.h"

#include <QImage>
#include <QDebug>

extern "C"
{
#include "libavcodec/packet.h"
#include "libavutil/frame.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}

#include "settings.h"
#include "recordingdevice.h"

namespace recorder
{

struct FrameWorker::impl_t
{
    Settings settings;
    std::shared_ptr<RecordingDevice> device;
    AVFrame* rgbFrame;
    AVFrame* frame;
    uint8_t* buffer;

    impl_t(const Settings& settings, const std::shared_ptr<RecordingDevice>& device)
        : settings {settings}
        , device {device}
        , rgbFrame {av_frame_alloc()}
        , frame {av_frame_alloc()}
    {
        const auto width = settings.resolution.width();
        const auto height = settings.resolution.height();
        const auto numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, width, height, 1);
        buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t)); //TODO make normal LOL
        av_image_fill_arrays(rgbFrame->data, rgbFrame->linesize, buffer, AV_PIX_FMT_RGB24, width, height, 1);
    }

    ~impl_t()
    {
        av_frame_free(&rgbFrame);
        av_frame_free(&frame);
        av_free(buffer);
    }
};

FrameWorker::FrameWorker(const Settings& settings, const std::shared_ptr<RecordingDevice>& device)
{
    createImpl(settings, device);

}

FrameWorker::~FrameWorker()
{
    qDebug() << Q_FUNC_INFO;
}

void FrameWorker::processFrame()
{
    struct Packet
    {
        AVPacket packet;

        Packet()
        {
            av_init_packet(&packet); // TODO update later
        }

        ~Packet()
        {
            av_packet_unref(&packet);
        }
    };

    Packet packet;

    if (av_read_frame(impl().device->formatCtx(), &packet.packet) < 0) {
        return;
    }

    if (avcodec_send_packet(impl().device->codecCtx(), &packet.packet) != 0) {
        return;
    }

    if (avcodec_receive_frame(impl().device->codecCtx(), impl().frame) == 0) {
        sws_scale(impl().device->swsCtx(), impl().frame->data, impl().frame->linesize, 0,
                  impl().device->codecCtx()->height,
                  impl().rgbFrame->data, impl().rgbFrame->linesize);

        QImage image(impl().rgbFrame->data[0], impl().settings.resolution.width(),
                     impl().settings.resolution.height(), QImage::Format_RGB888);

        emit frameCaptured(image);
    }
}

}
