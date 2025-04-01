#pragma once

#include <memory>

namespace recorder
{

class RecordingDevice;
struct StreamOptions;

class RecordingDeviceFactory
{
public:
    enum class Type : uint8_t
    {
        VideoCapture,
        SoundCapture
    };

    static std::shared_ptr<RecordingDevice> create(const Type type,  const StreamOptions& options);
};

}

