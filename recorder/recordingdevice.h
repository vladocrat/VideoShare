#pragma once

#include "pimpl.h"

struct AVFormatContext;
struct AVCodecContext;
struct SwsContext;

namespace recorder
{

class RecordingDevice
{
public:
    RecordingDevice(AVFormatContext* formatCtx, AVCodecContext* codecCtx, SwsContext* swsCtx);
    ~RecordingDevice();

    AVFormatContext* const formatCtx() const;
    AVCodecContext* const codecCtx() const;
    SwsContext* const swsCtx() const;

private:
    RecordingDevice() = delete;
    RecordingDevice(RecordingDevice&&) = delete;

private:
    DECLARE_PIMPL
};

}
