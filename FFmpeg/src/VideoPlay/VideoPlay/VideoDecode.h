/*!
 * \class VideoDecode.h
 *
 * \brief 视频解码类，在这个类中调用FFmpeg进行解码
 *
 * \author 戏中人
 *
 * \Contact: 2745308980@qq.com
 *
 * \date 2022/12/10
 */
#pragma once

#include <QString>
#include <QSize>

struct AVRational;
struct AVFormatContext;
struct AVCodecContext;
struct AVPacket;
struct AVFrame;
struct SwsContext;
struct AVBufferRef;
class QImage;

class VideoDecode
{

public:
    VideoDecode();
    ~VideoDecode();

    bool open(const QString& url = QString());
    QImage read();
    void close();
    bool isEnd();
    //获取当前帧显示时间
    const qint64& pts();

private:
    void initFFmpeg();
    void showError(int err);
    qreal rationalToDouble(AVRational* rational);
    void clear();   //清空读取缓冲
    void free();    //释放资源

private:
    AVFormatContext*    m_formatContext;    //解封装上下文
    AVCodecContext*     m_codecContext;     //解码器上下文
    SwsContext*         m_swsContext;       //图像转换上下文
    AVPacket*           m_packet;           //数据包
    AVFrame*            m_frame;            //解码后的视频帧
    int                 m_videoIndex;       //视频流索引
    qint64              m_totalTime;        //视频总时长
    qint64              m_totalFrames;      //视频总帧数
    qint64              m_obtainFrames;     //视频当前获取到的帧数
    qint64              m_pts;              //图像帧的显示时间
    qreal               m_frameRate;        //视频帧率
    QSize               m_size;             //视频分辨率大小
    char*               m_error;            //保存异常信息
    bool                m_isEnd;            //视频是否读取完成
    uchar*              m_buffer;           //YUV图像需要转换为RGBA图像，用于保存转换后的数据

};

