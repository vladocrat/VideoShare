#pragma once

#include <QQuickPaintedItem>

#include "pimpl.h"

class PixmapImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPixmap frame WRITE setPixmap FINAL)
public:
    PixmapImage();
    ~PixmapImage();

    void setPixmap(const QPixmap& pixmap);

    void paint(QPainter* painter) override;
    static void registerType();

private:
    DECLARE_PIMPL
};
