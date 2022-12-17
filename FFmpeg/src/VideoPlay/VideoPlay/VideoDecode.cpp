/*!
 * \class VideoDecode.cpp
 *
 * \brief 视频解码类，在这个类中调用FFmpeg进行解码 
 *
 * \author 戏中人
 *
 * \Contact: 2745308980@qq.com
 *
 * \date 2022/12/11
 */

#include "VideoDecode.h"
#include <QMutex>
#include <QTime>
#include <QImage>
#include <QDebug>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/avutil.h"
#include "libavutil/imgutils.h"
}

#define ERROR_LEN 1024  // 异常信息数组长度
#define PRINT_LOG 1

VideoDecode::VideoDecode() :
    m_formatContext(nullptr),
    m_codecContext(nullptr),
    m_swsContext(nullptr),
    m_packet(nullptr),
    m_frame(nullptr),
    m_videoIndex(0),
    m_totalTime(0),
    m_totalFrames(0),
    m_obtainFrames(0),
    m_pts(0),
    m_frameRate(0),
    m_isEnd(false),
    m_buffer(nullptr)
{
    m_error = new char[ERROR_LEN];
}

VideoDecode::~VideoDecode()
{
    close();
}

/**
 * 打开媒体文件，或者流媒体，如 rtsp、strp、http
 */
bool VideoDecode::open(const QString &url)
{
    if (url.isEmpty() || url.isNull())
    {
        return false;
    }

    AVDictionary* dict = nullptr;
    /**
     * 设置rtsp流使用tcp打开，如果打开失败错误信息为【Error number -135 occurred】可以切换（UDP、tcp、udp_multicast、http），
     * 比如vlc推流就需要使用udp打开
     */
    av_dict_set(&dict, "rtsp_transport", "tcp", 0);
    /**
     * 设置最大复用或解复用延迟（以微秒为单位）。当通过【UDP】 接收数据时，解复用器尝试重新排序接收到的数据包（因为它们可能无序到达，
     * 或者数据包可能完全丢失）。这可以通过将最大解复用延迟设置为零（通过max_delayAVFormatContext 字段）来禁用。
     */
    av_dict_set(&dict, "max_delay", "3", 0);
    /**
     * 以微秒为单位设置套接字 TCP I/O 超时，如果等待时间过短，也可能会还没连接就返回了。
     */
    av_dict_set(&dict, "timeout", "1000000", 0);
    //dict 为参数设置
    int ret = avformat_open_input(&m_formatContext, url.toStdString().data(), nullptr, &dict);

    //释放参数字典
    if (dict)
    {
        av_dict_free(&dict);
    }

    if (ret < 0)
    {
        //打开视频失败
        showError(ret);
        free();
        return false;
    }

    ret = avformat_find_stream_info(m_formatContext, nullptr);
    if (ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    m_totalTime = m_formatContext->duration / (AV_TIME_BASE / 1000);  //计算总时长为毫秒
    qDebug() << QString("视频总时长：%1 ms，[%2]").arg(m_totalTime).arg(QTime::fromMSecsSinceStartOfDay(int(m_totalTime)).toString("HH:mm:ss zzz"));

    //查找视频流ID
    m_videoIndex = av_find_best_stream(m_formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (m_videoIndex < 0)
    {
        showError(m_videoIndex);
        free();
        return false;
    }

    //通过视频流索引获取视频流
    AVStream* videoStream = m_formatContext->streams[m_videoIndex];

    // 获取视频图像分辨率（AVStream中的AVCodecContext在新版本中弃用，改为使用AVCodecParameters）
    m_size.setWidth(videoStream->codecpar->width);
    m_size.setHeight(videoStream->codecpar->height);

    //视频帧率
    m_frameRate = rationalToDouble(&videoStream->avg_frame_rate);

    // 通过解码器ID获取视频解码器（新版本返回值必须使用const）
    const AVCodec* codec = avcodec_find_decoder(videoStream->codecpar->codec_id);
    m_totalFrames = videoStream->nb_frames;

    qDebug() << QString("分辨率：[w:%1,h:%2] 帧率：%3  总帧数：%4  解码器：%5")
        .arg(m_size.width()).arg(m_size.height()).arg(m_frameRate).arg(m_totalFrames).arg(codec->name);

    // 分配AVCodecContext并将其字段设置为默认值。
    m_codecContext = avcodec_alloc_context3(codec);

    if (!m_codecContext)
    {
        qWarning() << "创建视频解码器上下文失败！";
        free();
        return false;
    }

    //使用视频流的codecpar为解码器上下文赋值
    ret = avcodec_parameters_to_context(m_codecContext, videoStream->codecpar);
    if (ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    //允许不符合规范的加速技巧
    m_codecContext->flags2 |= AV_CODEC_FLAG2_FAST;
    //解码的线程数
    m_codecContext->thread_count = 8;

    // 初始化解码器上下文，如果之前avcodec_alloc_context3传入了解码器，这里设置NULL就可以
    ret = avcodec_open2(m_codecContext, nullptr, nullptr);
    if (ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    // 分配AVPacket并将其字段设置为默认值
    m_packet = av_packet_alloc();
    if (!m_packet)
    {
        qWarning() << "av_packet_alloc() Error！";
        free();
        return false;
    }

    //分配AVFrame并将其字段设置为默认值
    m_frame = av_frame_alloc();
    if (!m_frame)
    {
        qWarning() << "av_frame_alloc() Error！";
        free();
        return false;
    }

    //获取到图像字节数
    int size = av_image_get_buffer_size(AV_PIX_FMT_RGBA, m_size.width(), m_size.height(), 4);
    //多分配一点，防止在少部分视频图像在使用sws_scale()拷贝时会超出数组长度
    m_buffer = new uchar[size + 1000];

    m_isEnd = false;

    return true;
}

QImage VideoDecode::read()
{
    //如果没有打开则返回
    if (!m_formatContext)
    {
        return QImage();
    }

    //读取下一帧数据
    int readRet = av_read_frame(m_formatContext, m_packet);
    if (readRet < 0)
    {
        // 读取完成后向解码器中传如空AVPacket，否则无法读取出最后几帧
        avcodec_send_packet(m_codecContext, m_packet);
    }
    else
    {
        //如果是视频流数据,则进行解码
        if (m_packet->stream_index == m_videoIndex)
        {
            //计算当前帧时间
            //显示时间戳
            m_packet->pts = qRound64(m_packet->pts*(1000 * rationalToDouble(&m_formatContext->streams[m_videoIndex]->time_base)));
            //解码时间戳
            m_packet->dts = qRound64(m_packet->dts*(1000 * rationalToDouble(&m_formatContext->streams[m_videoIndex]->time_base)));
            //将读取到的数据包传入解码器
            int ret = avcodec_send_packet(m_codecContext, m_packet);
            if (ret < 0)
            {
                showError(ret);
            }
        }

    }
    //调用了av_read_frame()需要释放,释放数据包，引用计数-1，为0时释放空间
    av_packet_unref(m_packet);

    int ret = avcodec_receive_frame(m_codecContext, m_frame);
    if (ret < 0)
    {
        av_frame_unref(m_frame);
        if (readRet < 0)
        {
            m_isEnd = true; //当无法读取到AVPacket并且解码器中也没有数据时表示读取完成
        }
        return QImage();
    }
    m_pts = m_frame->pts;
    if (!m_swsContext)
    {
        m_swsContext = sws_getCachedContext(m_swsContext,
            m_frame->width, m_frame->height,
            (AVPixelFormat)m_frame->format,
            m_size.width(), m_size.height(),
            AV_PIX_FMT_RGBA, SWS_BILINEAR, nullptr, nullptr, nullptr);
    }
    if (!m_swsContext)
    {
        qWarning() << "sws_getCachedContext() error";
        free();
        return QImage();
    }

    //AVFrame转QImage
    uchar* data[] = { m_buffer };
    int lines[4];
    //使用像素格式pix_fmt和宽度填充图像的平面线条大小。
    av_image_fill_linesizes(lines, AV_PIX_FMT_RGBA, m_frame->width);
    ret = sws_scale(m_swsContext, m_frame->data, m_frame->linesize, 0, m_frame->height, data, lines);
    QImage image(m_buffer, m_frame->width, m_frame->height, QImage::Format_RGBA8888);

    return image;
}

//关闭视频播放,并释放内存
void VideoDecode::close()
{
    clear();
    free();

    m_totalTime = 0;
    m_videoIndex = 0;
    m_totalFrames = 0;
    m_obtainFrames = 0;
    m_pts = 0;
    m_frameRate = 0;
    m_size = QSize(0, 0);
}

bool VideoDecode::isEnd()
{
    return m_isEnd;
}

const qint64 &VideoDecode::pts()
{
    return m_pts;
}

void VideoDecode::initFFmpeg()
{
    static bool isFirst = true;
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if (isFirst)
    {
        /**
         * 初始化网络库,用于打开网络流媒体，此函数仅用于解决旧GnuTLS或OpenSSL库的线程安全问题。
         * 一旦删除对旧GnuTLS和OpenSSL库的支持，此函数将被弃用，并且此函数不再有任何用途。
         */
        avformat_network_init();
        isFirst = false;
    }
}

void VideoDecode::showError(int err)
{
    memset(m_error, 0, ERROR_LEN);    //将数组都置为0
    av_strerror(err, m_error, ERROR_LEN);
    qWarning() << "DecodeVideo Error: " << m_error;
}

qreal VideoDecode::rationalToDouble(AVRational * rational)
{
    qreal frameRate = (rational->den == 0) ? 0 : (qreal(rational->num) / rational->den);
    return frameRate;
}

//清空读取缓冲
void VideoDecode::clear()
{
    // 因为avformat_flush不会刷新AVIOContext (s->pb)。如果有必要，在调用此函数之前调用avio_flush(s->pb)。
    if (m_formatContext && m_formatContext->pb)
    {
        avio_flush(m_formatContext->pb);
    }
    if (m_formatContext)
    {
        avformat_flush(m_formatContext);   // 清理读取缓冲
    }
}

void VideoDecode::free()
{
    // 释放上下文swsContext。
    if (m_swsContext)
    {
        sws_freeContext(m_swsContext);
        m_swsContext = nullptr;             // sws_freeContext不会把上下文置NULL
    }
    // 释放编解码器上下文和与之相关的所有内容，并将NULL写入提供的指针
    if (m_codecContext)
    {
        avcodec_free_context(&m_codecContext);
    }
    // 关闭并失败m_formatContext，并将指针置为null
    if (m_formatContext)
    {
        avformat_close_input(&m_formatContext);
    }
    if (m_packet)
    {
        av_packet_free(&m_packet);
    }
    if (m_frame)
    {
        av_frame_free(&m_frame);
    }
    if (m_buffer)
    {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
}
