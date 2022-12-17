#pragma once

#include <QThread>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
}

class AudioThread : public QThread
{
    Q_OBJECT

public:
    AudioThread(QObject *parent = nullptr);
    ~AudioThread();

    void setStopFlag(bool);

private:
    bool stopFlag;

protected:
    void run() override;
};
