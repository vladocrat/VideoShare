#pragma once

#include <QString>
#include <QRect>
#include <QSize>

namespace recorder
{

struct Process
{
    QString name;
    QRect geometry;
    QSize screenSize;

    bool operator==(const Process& other) const;
};

}
