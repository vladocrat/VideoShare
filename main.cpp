#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "recorder/processenumerator.h"
#include "recorder/process.h"
#include "recorder/recorder.h"

#include "devicesenumerationmodel.h"
#include "frameprovider.h"
#include "pixmapimage.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    PixmapImage::registerType();

    DevicesEnumerationModel model;
    FrameProvider provider;
    recorder::Recorder* recorder = new recorder::Recorder;

    QObject::connect(recorder, &recorder::Recorder::frameRecieved, &provider, &FrameProvider::setFrame);
    recorder::Settings settings;
    settings.fps = 500;
    settings.proc = recorder::ProcessEnumerator::enumerate()[1];
    settings.resolution = settings.proc.screenSize;
    recorder->setSettings(settings);
    recorder->start();

    for (const auto& p : recorder::ProcessEnumerator::enumerate()) {
        qDebug() << p.geometry << " " << p.screenSize << " " << p.name;
        model.append(p);
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("enumModel", &model);
    engine.rootContext()->setContextProperty("frameProvider", &provider);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("VideoSharing", "Main");

    return app.exec();
}
