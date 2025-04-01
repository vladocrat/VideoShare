#pragma once

#include <QObject>

extern "C"
{
//! NEEDS TO BE IN A HEADER FILE,
//! otherwise av_image_get_buffer_size and av_image_fill_arrays break
#include "libavutil/imgutils.h"
}

#include "pimpl.h"

namespace recorder
{

struct Settings;
class RecordingDevice;

class FrameWorker : public QObject
{
    Q_OBJECT
public:
    FrameWorker(const Settings& settings, const std::shared_ptr<RecordingDevice>& device);
    ~FrameWorker();

public slots:
    void processFrame();

signals:
    void frameCaptured(const QImage& image);

private:
    DECLARE_PIMPL
};

}
