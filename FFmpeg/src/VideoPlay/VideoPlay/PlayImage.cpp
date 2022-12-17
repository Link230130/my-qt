#include <QPainter>
#include "PlayImage.h"
#include <QDebug>
#include <QThread>

PlayImage::PlayImage(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

PlayImage::~PlayImage()
{
}

void PlayImage::paintEvent(QPaintEvent * event)
{
    //qDebug() << "PlayImage::paintEvent thread id=" << QThread::currentThreadId();
    if (!m_pixmap.isNull())
    {
        QPainter painter(this);
#if 0
        // 经过粗略测试，QImage先缩放后转为QPixmap的方式在图像比较小时耗时少，图片越大耗时越大
        QPixmap pixmap = QPixmap::fromImage(m_image.scaled(this->size(), Qt::KeepAspectRatio));
        // 先将QImage转换为QPixmap再进行缩放则耗时比较少，并且稳定，不会因为缩放图片大小而产生太大影响
        QPixmap pixmap1 = QPixmap::fromImage(m_image).scaled(this->size(), Qt::KeepAspectRatio);
#endif
        m_mutex.lock();
        QPixmap pixmap = m_pixmap.scaled(this->size(), Qt::KeepAspectRatio);
        m_mutex.unlock();
        int x = (this->width() - pixmap.width()) / 2;
        int y = (this->height() - pixmap.height()) / 2;
        painter.drawPixmap(x, y, pixmap);
    }
    QWidget::paintEvent(event);
}

void PlayImage::updateImage(const QImage& image)
{
    //qDebug() << "PlayImage::updateImage thread id=" << QThread::currentThreadId();
    updatePixmap(QPixmap::fromImage(image));
}

void PlayImage::updatePixmap(const QPixmap& pixmap)
{
    m_mutex.lock();
    m_pixmap = pixmap;
    m_mutex.unlock();
    update();
}
