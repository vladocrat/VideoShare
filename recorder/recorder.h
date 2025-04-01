#pragma once

#include <QObject>

#include "settings.h"
#include "pimpl.h"

namespace recorder
{

class Recorder final : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(Settings settings READ settings WRITE setSettings NOTIFY settingsChanged FINAL)
public:
    Recorder();
    ~Recorder();

    void settings() const;

public slots:
    void setSettings(const Settings&);
    void start();
    void stop();

signals:
    void settingsChanged();
    void frameRecieved(const QPixmap&);

private:
    DECLARE_PIMPL
};

}
