#include "recordingdevicefactory.h"

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavutil/imgutils.h>
}

#include "recordingdevice.h"
#include "streamoptions.h"

/*
        const AVInputFormat* inputFormat = av_find_input_format("gdigrab");
        if (!inputFormat) {
            std::cerr << "Cannot find input format 'gdigrab'" << std::endl;
            return;
        }

        AVDictionary* options = nullptr;
        av_dict_set(&options, "framerate", "480", 0);
        av_dict_set(&options, "probesize", "500M", 0);
        av_dict_set(&options, "offset_x", "-1920", 0);
        av_dict_set(&options, "offset_y", "162", 0);
        av_dict_set(&options, "video_size", "1920x1080", 0);
        av_dict_set(&options, "title", "Battle.net", 0);

        if (avformat_open_input(&formatCtx, "desktop", inputFormat, &options) != 0) {
            std::cerr << "Cannot open input" << std::endl;
            return;
        }

        if (avformat_find_stream_info(formatCtx, &options) < 0) {
            std::cerr << "Cannot find stream info" << std::endl;
            return;
        }

        int videoStreamIndex = -1;
        for (unsigned int i = 0; i < formatCtx->nb_streams; i++) {
            if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoStreamIndex = i;
                break;
            }
        }

        if (videoStreamIndex == -1) {
            std::cerr << "Cannot find a video stream" << std::endl;
            return;
        }

        AVCodecParameters* codecPar = formatCtx->streams[videoStreamIndex]->codecpar;
        const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);
        if (!codec) {
            std::cerr << "Cannot find codec" << std::endl;
            return;
        }

        codecCtx = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(codecCtx, codecPar);

        if (avcodec_open2(codecCtx, codec, nullptr) < 0) {
            std::cerr << "Cannot open codec" << std::endl;
            return;
        }

        swsCtx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
                                codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24,
                                SWS_BILINEAR, nullptr, nullptr, nullptr);
*/


namespace recorder
{

std::shared_ptr<RecordingDevice> RecordingDeviceFactory::create(const Type type, const StreamOptions& options)
{
    switch (type) {
    case Type::VideoCapture: {
#ifdef WIN32
        const auto inputFormat = av_find_input_format("gdigrab");
        auto dictionary = options.toDictionary();

        AVFormatContext* formatCtx { nullptr };

        if (avformat_open_input(&formatCtx, "desktop", inputFormat, &dictionary) != 0) {
            return nullptr;
        }

        if (avformat_find_stream_info(formatCtx, &dictionary) < 0) {
            return nullptr;
        }

        int32_t videoStreamIndex = -1;
        for (int32_t i = 0; i < formatCtx->nb_streams; i++) {
            if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoStreamIndex = i;
                break;
            }
        }

        if (videoStreamIndex == -1) {
            return nullptr;
        }

        const auto codecPar = formatCtx->streams[videoStreamIndex]->codecpar;
        const auto codec = avcodec_find_decoder(codecPar->codec_id);

        if (!codec) {
            return nullptr;
        }

        const auto codecCtx = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(codecCtx, codecPar);

        if (avcodec_open2(codecCtx, codec, nullptr) < 0) {
            return nullptr;
        }

        const auto swsCtx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
                                codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24,
                                SWS_BILINEAR, nullptr, nullptr, nullptr);

        return std::make_shared<RecordingDevice>(formatCtx, codecCtx, swsCtx);

#endif

        break;
    }
    case Type::SoundCapture: {
        return nullptr;
        break;
    }
    default: {
        return nullptr;
    }
    }

    return nullptr;
}

}
