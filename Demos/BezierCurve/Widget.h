#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;


private:
    //初始化参数
    void initParam();
    //检查鼠标按下的点
    bool checkMousePress(const QPoint &p);
    //计算两点间的距离
    double distance(const QPointF p1, const QPointF p2);

    // 曲线上的点
    QList<QPointF> points;
    //起点
    QPointF startP;
    //终点
    QPointF endP;
    //控制点1
    QPointF cP1;
    //控制点2
    QPointF cP2;
    //鼠标按下坐标
    QPoint mousePressPos;
    //鼠标按下点的下标
    int mousePressIndex;
    //鼠标位置显示文本
    QString mousePosText;
};
#endif // WIDGET_H
