#pragma once

#include <cstdint>
#include <qsize.h>

struct AVDictionary;

namespace recorder
{

struct StreamOptions
{
    uint16_t frameRate;
    uint16_t probesize;
    int32_t offsetX;
    int32_t offsetY;
    QSize resolution;

    AVDictionary* toDictionary() const;
};

}
