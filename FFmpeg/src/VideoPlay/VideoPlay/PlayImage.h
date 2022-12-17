#pragma once

#include <QWidget>
#include <QMutex>

class PlayImage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayImage(QWidget *parent = nullptr);
    ~PlayImage();

    void updateImage(const QImage& image);
    void updatePixmap(const QPixmap& pixmap);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap m_pixmap;
    QMutex m_mutex;

};
