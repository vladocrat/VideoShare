#include "streamoptions.h"

#include <QDebug>

extern "C"
{
#include "libavutil/dict.h"
}

namespace
{

std::string sizeToString(const QSize& size)
{
    return std::to_string(size.width()) + "x" + std::to_string(size.height());
}

}

namespace recorder
{

AVDictionary* StreamOptions::toDictionary() const
{
    AVDictionary* dict { nullptr };

    qDebug() << std::to_string(frameRate).c_str();
    qDebug() << (std::to_string(probesize) + "M").c_str();
    qDebug() << std::to_string(offsetX).c_str();
    qDebug() << std::to_string(offsetY).c_str();
    qDebug() << sizeToString(resolution).c_str();

    av_dict_set(&dict, "framerate", std::to_string(frameRate).c_str(), 0);
    av_dict_set(&dict, "probesize", (std::to_string(probesize) + "M").c_str(), 0);
    av_dict_set(&dict, "offset_x", std::to_string(offsetX).c_str(), 0);
    av_dict_set(&dict, "offset_y", std::to_string(offsetY).c_str(), 0);
    av_dict_set(&dict, "video_size", sizeToString(resolution).c_str(), 0);
    av_dict_set(&dict, "title", "Battle.net", 0);

    return dict;
}

}
