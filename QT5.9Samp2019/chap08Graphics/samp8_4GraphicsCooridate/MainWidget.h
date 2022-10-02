#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#pragma once

#include <QWidget>
#include <QGraphicsScene>

#include "ui_MainWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_mouseMovePoint(QPoint point);
    void on_mouseClicked(QPoint point);

private:
    void iniGraphicsSystem();

    QGraphicsScene *scene;
private:
    Ui::MainWidgetClass ui;
};
#endif // !MAINWIDGET_H