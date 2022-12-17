/*!
 * \class ReadThread.cpp
 *
 * \brief 读取视频图像数据线程，在线程中解码视频
 *
 * \author 戏中人
 *
 * \Contact: 2745308980@qq.com
 *
 * \date 2022/12/11
 */

#include "ReadThread.h"
#include <QEventLoop>
#include <QTimer>
#include <QImage>
#include <QDebug>

ReadThread::ReadThread(QObject *parent)
    : QThread(parent)
    , m_play(false)
    , m_pause(false)
{
    m_videoDecode = new VideoDecode;
    qRegisterMetaType<PlayState>("PlayState");  //注册自定义枚举类型，用于信号与槽参数传递
}

ReadThread::~ReadThread()
{
    if (m_videoDecode)
    {
        delete m_videoDecode;
    }
}

//打开视频
void ReadThread::open(const QString& url)
{
    if (!this->isRunning())
    {
        m_url = url;
        this->start();
    }
}

//控制视频播放暂停
void ReadThread::pause(bool flag)
{
    m_pause = flag;
}

//关闭视频播放
void ReadThread::close()
{
    m_play = false;
    m_pause = false;
}

const QString & ReadThread::url()
{
    return m_url;
}

//非阻塞延时
void sleepMsec(int msec)
{
    if (msec <= 0)
    {
        return;
    }
    //定义一个新的事件循环
    QEventLoop loop;
    //创建单次定时器，槽函数为事件循环的退出函数
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

void ReadThread::run()
{
    //qDebug() << "执行run方法";
    //打开网络流会比较慢，需要放到线程里处理，否则会卡住UI线程
    bool ret = m_videoDecode->open(m_url);
    //qDebug() << "m_videoDecode->open结束";
    if (ret)
    {
        m_play = true;
        m_endTime2.start();
        m_endTime1.start();
        emit playState(PLAY);
    }
    else
    {
        qWarning() << QString("打开视频失败，url=%1").arg(m_url);
    }
    while (m_play)
    {
        while (m_pause)
        {
            sleepMsec(200);
        }
        QImage image = m_videoDecode->read();
        if (!image.isNull())
        {
            // 1倍速播放
#if 0
            sleepMsec(int(m_decodeVideo->pts() - m_endTime1.elapsed()));         // 不支持后退
#else
            sleepMsec(int(m_videoDecode->pts() - m_endTime2.elapsed()));         // 支持后退
#endif
            //qDebug() << "ReadThread::run threrad id=" << QThread::currentThreadId();
            emit updateImage(image);
        }
        else
        {
            //读取到无效图像时判断是否读取完成
            if (m_videoDecode->isEnd())
            {
                break;
            }
            // 这里不能使用QThread::msleep()延时，否则会很不稳定
            sleepMsec(1);
        }
    }
    qDebug() << "播放结束";
    m_videoDecode->close();
    emit playState(END);
}


