#pragma once

#include <QWidget>

#include "ui_Widget.h"
#include "AudioThread.h"
#include "PlayThread.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = Q_NULLPTR);

public slots:
    void on_audioBtn_clicked();
    void on_playBtn_clicked();

private:
    Ui::WidgetClass ui;
    AudioThread* audioThread;
    bool stopFlag;
    PlayThread* playThread;
};
