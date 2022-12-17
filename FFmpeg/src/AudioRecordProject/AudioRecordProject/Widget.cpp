/**
 * 这是一个录制原始音频但不带编码的小案例

 使用FFmpeg录制音频的基本步骤：
    1.注册输入设备
    2.获取输入格式
        用 ffmpeg -devices 可以查看在系统上支持的格式
        win系统采用的是 dshow 格式
    3.打开输入设备
    4.采集数据
    5.资源回收（关闭设备、关闭文件、回收格式上下文的堆区空间）

 */

#pragma execution_character_set("utf-8")

#include <QFile>

#include "Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , stopFlag(false)
{
    ui.setupUi(this);
    this->setWindowTitle("录制原始音频");

    //1.注册输入设备
    avdevice_register_all();

    audioThread = new AudioThread(this);
    //关闭窗口进行线程资源回收
    connect(this, &Widget::destroy, [=]() {
        audioThread->setStopFlag(true);
        audioThread->exit();
        audioThread->wait();
    });
    playThread = new PlayThread(this);
    connect(this, &Widget::destroy, [=]() {
        playThread->exit();
        playThread->wait();
    });
}

void Widget::on_audioBtn_clicked()
{
    if (!stopFlag)
    {
        audioThread->setStopFlag(stopFlag);
        audioThread->start();
        ui.audioBtn->setText("停止录音");
        stopFlag = true;
    }
    else
    {
        audioThread->setStopFlag(stopFlag);
        audioThread->exit();
        audioThread->wait();
        ui.audioBtn->setText("开始录音");
    }
}

void Widget::on_playBtn_clicked()
{
    playThread->start();
}