#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H

#include <QWidget>

class RoundButton : public QWidget
{
    Q_OBJECT
public:
    explicit RoundButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    void drawMyArc(QPainter &p, qreal startAngle, qreal sweepLength);
signals:

public slots:
};

#endif // ROUNDBUTTON_H
