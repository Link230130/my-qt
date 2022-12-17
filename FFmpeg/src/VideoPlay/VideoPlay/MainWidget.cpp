/*!
 * \class MainWidget.cpp
 *
 * \brief 视频播放主界面类
 *
 * \author 戏中人
 *
 * \Contact: 2745308980@qq.com
 *
 * \date 2022/12/11
 */

#include "MainWidget.h"

#include <QFileDialog>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString("Qt+FFmpeg视频播放(软件解码)"));

    m_readThread = new ReadThread();
    connect(m_readThread, &ReadThread::updateImage, ui.playImage, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::updateImage, ui.playImage_1, &PlayImage::updateImage, Qt::DirectConnection);
    /*connect(m_readThread, &ReadThread::updateImage, ui.playImage_2, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::updateImage, ui.playImage_3, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::updateImage, ui.playImage_4, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::updateImage, ui.playImage_5, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::updateImage, ui.playImage_6, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::updateImage, ui.playImage_7, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::updateImage, ui.playImage_8, &PlayImage::updateImage, Qt::DirectConnection);*/
    
    connect(m_readThread, &ReadThread::playState, this, &MainWidget::on_playState);
    ui.url->setText("C:/Users/tian.ji/Desktop/序列 01.mp4");
}


MainWidget::~MainWidget()
{
    if (m_readThread)
    {
        m_readThread->close();
        m_readThread->wait();
        delete m_readThread;
    }
}

//开始播放/结束播放
void MainWidget::on_startBtn_clicked()
{
    if (ui.startBtn->text() == "开始")
    {
        m_readThread->open(ui.url->text());
    }
    else
    {
        m_readThread->close();
    }
    qDebug() << "MainWidget::on_startBtn_clicked thread id=" << QThread::currentThreadId();
}

//选择文件
void MainWidget::on_selectBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择播放视频", "C:/", "视频 (*.mp4 *.m4v *.mov *.avi *.flv);; 其它(*)");
    if (fileName.isEmpty())
    {
        return;
    }
    ui.url->setText(fileName);
}

//暂停播放
void MainWidget::on_pauseBtn_clicked()
{
    if (ui.pauseBtn->text() == "暂停")
    {
        m_readThread->pause(true);
        ui.pauseBtn->setText("继续");
    }
    else
    {
        m_readThread->pause(false);
        ui.pauseBtn->setText("暂停");
    }
}

void MainWidget::on_playState(ReadThread::PlayState state)
{
    if (state == ReadThread::PLAY)
    {
        this->setWindowTitle(QString("正在播放%1").arg(m_readThread->url()));
        ui.startBtn->setText("停止播放");
    }
    else
    {
        ui.startBtn->setText("开始");
        ui.pauseBtn->setText("暂停");
        this->setWindowTitle("Qt+FFmpeg视频播放(软件解码)");
    }
}
