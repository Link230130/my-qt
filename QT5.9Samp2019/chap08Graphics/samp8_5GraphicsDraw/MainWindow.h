#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QKeyEvent>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);


private:
    void iniUI();

    static const int    ItemId = 1;//图形项自定义数据的key
    static const int    ItemDesciption = 2;//图形项自定义数据的key
    int                 seqNum;//用于图形项的编号，每个图形项有一个编号
    int                 frontZ;//用于bring to front
    int                 backZ;//用于bring to back
    QLabel              *labViewCord;//view坐标
    QLabel              *labSceneCord;//scene坐标
    QLabel              *labItemCord;//item坐标
    QLabel              *labItemInfo;//item信息
    QGraphicsScene      *scene;//场景

private slots:
    //鼠标移动
    void on_mouseMovePoint(QPoint point);
    //鼠标单击
    void on_mouseClicked(QPoint point);
    //鼠标双击
    void on_mouseDoubleClick(QPoint point);
    //按键
    void on_keyPress(QKeyEvent *event);

    void on_actItem_Rect_triggered();

    void on_actItem_Ellipse_triggered();

    void on_actItem_Polygon_triggered();
    //删除
    void on_actEdit_Delete_triggered();
    //放大
    void on_actZoomIn_triggered();
    //缩小
    void on_actZoomOut_triggered();
    //恢复
    void on_actRestore_triggered();
    //逆时针旋转
    void on_actRotateLeft_triggered();
    //顺时针旋转
    void on_actRotateRight_triggered();
    //前置
    void on_actEdit_Front_triggered();
    //后置
    void on_actEdit_Back_triggered();

    void on_actItem_Line_triggered();
    //文本
    void on_actItem_Text_triggered();
    //组合
    void on_actGroup_triggered();
    //取消组合
    void on_actGroupBreak_triggered();

    void on_actItem_Circle_triggered();

    void on_actItem_Triangle_triggered();

private:
    Ui::MainWindowClass ui;
};
#endif // !MAINWINDOW_H