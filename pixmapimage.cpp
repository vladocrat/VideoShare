#include "pixmapimage.h"

#include <QPixmap>
#include <QPainter>
#include <QQmlEngine>

struct PixmapImage::impl_t
{
    QPixmap frame;
};

PixmapImage::PixmapImage()
{
    createImpl();
}

PixmapImage::~PixmapImage()
{

}

void PixmapImage::setPixmap(const QPixmap& pixmap)
{
    impl().frame = pixmap;
    update();
}

void PixmapImage::paint(QPainter* painter)
{
    painter->drawPixmap(0, 0, impl().frame);
}

void PixmapImage::registerType()
{
    qmlRegisterType<PixmapImage>("PixmapImage", 1, 0, "PixmapImage");
}
