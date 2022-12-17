#include "PlayThread.h"
#include <QDebug>
#include <QFile>

int     bufferLen;  //缓冲区长度
char*   bufferData;   //缓冲区数据
static int c = 0;

//回调函数
void _audioCallback(void *userdata, Uint8 * stream, int len)
{
    qDebug() << c++ << "-----------拉流线程ID: " << QThread::currentThreadId() << "bufferLen=" <<bufferLen;
    //清空缓冲区
    SDL_memset(stream, 0, len);
    if (bufferLen <= 0)
    {

        return;
    }
    //确定len的实际长度
    len = (len > bufferLen) ? bufferLen : len;
    //填充数据buffer
    SDL_MixAudio(stream, (Uint8*)bufferData, len, SDL_MIX_MAXVOLUME);
    //数据的指针要进行移动
    bufferData += len;
    bufferLen -= len;
}


PlayThread::PlayThread(QObject *parent)
    : QThread(parent)
{
    qDebug() << "PlayThread构造";
}

PlayThread::~PlayThread()
{
    qDebug() << "PlayThread析构";
}

void PlayThread::run()
{
    //     SDL_version version;
    //     SDL_VERSION(&version);
    //     qDebug() << version.major << version.minor << version.patch;

    //1.初始化音频子系统
    SDL_Init(SDL_INIT_AUDIO);

    //2.确定播放音频的相关参数
    SDL_AudioSpec spc;
    spc.freq = 44100;   //采样率
    spc.format = AUDIO_S16LSB;
    spc.channels = 2;   //通道
    spc.callback = _audioCallback;  //回调函数
    spc.samples = 1024; //音频缓冲区
    

    //3.打开音频文件
    QFile file("./test.pcm");
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen())
    {
        qDebug() << "文件打开失败";
        SDL_Quit(); //使用SDL_Init初始化子系统后需要进行退出
        return;
    }

    //4.按照格式打开音频
    SDL_OpenAudio(&spc, nullptr);

    //5.播放音频（或视频，都是通过推流和拉流的方式进行实现）
    //push:程序主动推送数据给设备
    //pull:音频设备主动向程序拉取数据
    SDL_PauseAudio(0);  //0为播放，1为暂停

    char audio_buf[4096];
    while (!isFinished())
    {
        bufferLen = file.read(audio_buf, sizeof(char[4096]));
        if (bufferLen <= 0)
        {
            //代表到文件末尾
            break;
        }
        bufferData = audio_buf;
        //休眠，等待回调函数拉取数据
        while (bufferLen > 0)
        {
            qDebug() << "推流线程ID: " << QThread::currentThreadId();
            SDL_Delay(1);
        }
    }
}
