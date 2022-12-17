/**
 * 录音线程
 */

#include <QFile>
#include "AudioThread.h"

#pragma execution_character_set("utf-8")

AudioThread::AudioThread(QObject *parent)
    : QThread(parent)
{
    stopFlag = false;
}

AudioThread::~AudioThread()
{
}

void AudioThread::setStopFlag(bool flag)
{
    this->stopFlag = flag;
}

void AudioThread::run()
{
    //2.获取win系统中采集数据所支持的格式（dshow）
    const AVInputFormat * fmt = av_find_input_format("dshow");

    //定义采集音频数据的格式上下文
    AVFormatContext* ctx = nullptr;
    const char* audio_device = "audio=麦克风阵列 (Realtek High Definition Audio)";
    //3.打开输入的音频设备
    avformat_open_input(&ctx, audio_device, fmt, nullptr);

    //pcm为不带任何编码格式的音频文件
    //ffplay -ar 44100 -ac 2 -f s16le test.pcm命令进行播放
    QFile file("./test.pcm");
    file.open(QIODevice::WriteOnly);
    if (!file.isOpen())
    {
        return;
    }

    //4.采集数据
    AVPacket pkt;
    while (!stopFlag && 0 == av_read_frame(ctx, &pkt))
    {
        file.write((const char*)pkt.data, pkt.size);
    }

    //5.释放所用到的资源
    file.close();
    avformat_close_input(&ctx);
}
