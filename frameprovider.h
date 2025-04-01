#pragma once

#include <QQuickImageProvider>

#include "pimpl.h"

class FrameProvider final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap frame READ frame WRITE setFrame NOTIFY frameChanged FINAL)
public:
    FrameProvider();
    ~FrameProvider();

    QPixmap frame() const;

public slots:
    void setFrame(const QPixmap& newFrame);

signals:
    void frameChanged();

private:
    DECLARE_PIMPL
};

