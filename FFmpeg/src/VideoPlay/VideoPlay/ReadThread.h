/*!
 * \class ReadThread.h
 *
 * \brief 读取视频图像数据线程，在线程中解码视频 
 *
 * \author 戏中人
 *
 * \Contact: 2745308980@qq.com
 *
 * \date 2022/12/11
 */

#pragma once

#include <QThread>
#include <QElapsedTimer>
#include <QTime>
#include "VideoDecode.h"

class ReadThread : public QThread
{
    Q_OBJECT
public:
    //视频播放状态
    enum PlayState
    {
        PLAY,END
    };

public:
    explicit ReadThread(QObject *parent = nullptr);
    ~ReadThread();

    void open(const QString& url = QString());    //打开视频
    void pause(bool flag);      //暂停视频
    void close();               //关闭视频
    const QString& url();       //获取打开的视频地址
    
protected:
    void run() override;

signals:
    void updateImage(const QImage& image);      //将读取到的视频图像发送出去
    void playState(PlayState state);            //视频播放状态改变时触发

private:
    VideoDecode*    m_videoDecode;      //视频解码类
    QString         m_url;              //视频地址
    bool            m_play;             //播放控制
    bool            m_pause;              //暂停控制
    QElapsedTimer   m_endTime1;         //控制播放速度（精度高但不支持视频后退）
    QTime           m_endTime2;         //控制播放速度（支持后退）
};
