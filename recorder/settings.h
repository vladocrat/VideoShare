#pragma once

#include <QObject>

#include "process.h"

namespace recorder
{

struct Settings
{
    Process proc;
    uint16_t fps;
    QSize resolution;

    bool operator==(const Settings& other);
};

}
Q_DECLARE_METATYPE(recorder::Settings);
