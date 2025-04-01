#include "recorder.h"

#include <QThread>
#include <QTimer>
#include <QImage>
#include <QPixmap>

extern "C"
{
#include "libavdevice/avdevice.h"
}

#include "settings.h"
#include "frameworker.h"
#include "recordingdevicefactory.h"
#include "streamoptions.h"

#include <QDebug>

namespace recorder
{

struct Recorder::impl_t
{
    Settings settings;
    QThread workerThread;
    QTimer frameTimer;

    ~impl_t()
    {
        frameTimer.stop();
        workerThread.quit();
    }
};

Recorder::Recorder()
{
    createImpl();
    avdevice_register_all();
}

Recorder::~Recorder()
{

}

void Recorder::start()
{
    StreamOptions options; //TODO change
    options.probesize = 500;
    options.frameRate = impl().settings.fps;
    options.offsetX = -1920;
    options.offsetY = 162;
    options.resolution = impl().settings.resolution;

    const auto videoDevice = RecordingDeviceFactory::create(RecordingDeviceFactory::Type::VideoCapture,
                                                            options);

    if (videoDevice == nullptr) {
        qDebug() << "fuck you";
    }

    const auto worker = new FrameWorker(impl().settings, videoDevice);
    worker->moveToThread(&impl().workerThread);

    QObject::connect(&impl().workerThread, &QThread::finished, worker, &QObject::deleteLater);
    QObject::connect(worker, &FrameWorker::frameCaptured, this, [this](const QImage& img) {
        emit frameRecieved(QPixmap::fromImage(img));
    });

    impl().workerThread.start();

    QObject::connect(&impl().frameTimer, &QTimer::timeout, worker, &FrameWorker::processFrame);
    impl().frameTimer.start(1);
}

void Recorder::stop()
{
    impl().frameTimer.stop();
    impl().workerThread.quit();
}

void Recorder::setSettings(const Settings& settings)
{
    //! TODO temp
    // if (impl().settings == settings) {
    //     return;
    // }

    impl().settings = settings;
    emit settingsChanged();
}



}
