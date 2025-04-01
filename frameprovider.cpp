#include "frameprovider.h"

struct FrameProvider::impl_t
{
    QPixmap frame;
};

FrameProvider::FrameProvider()
{
    createImpl();
}

FrameProvider::~FrameProvider()
{

}

QPixmap FrameProvider::frame() const
{
    return impl().frame;
}

void FrameProvider::setFrame(const QPixmap& newFrame)
{
    impl().frame = newFrame;
    emit frameChanged();
}
