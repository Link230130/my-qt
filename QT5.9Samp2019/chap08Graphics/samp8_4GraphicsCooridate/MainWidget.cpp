
#include <QGraphicsItem>
#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.graphicsView->setCursor(Qt::CrossCursor);
    ui.graphicsView->setMouseTracking(true);
    ui.graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    connect(ui.graphicsView, SIGNAL(mouseMovePoint(QPoint)),
        this, SLOT(on_mouseMovePoint(QPoint)));
    connect(ui.graphicsView, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(on_mouseMovePoint(QPoint)));
    connect(ui.graphicsView, SIGNAL(mouseClicked(QPoint)),
        this, SLOT(on_mouseClicked(QPoint)));
    iniGraphicsSystem();
}

void MainWidget::resizeEvent(QResizeEvent * event)
{
    scene->setSceneRect(-ui.graphicsView->width() / 2 - 10, -ui.graphicsView->height() / 2 - 10,
        ui.graphicsView->width() - 20, ui.graphicsView->height() - 20);
    ui.viewSize->setText(QString("GraphicsView 坐标：左上角总是(0,0)，宽度=%1,高度=%2")
        .arg(ui.graphicsView->width()).arg(ui.graphicsView->height()));
    //Scene 的矩形区
    QRectF rectF = ui.graphicsView->sceneRect();
    ui.sceneRect->setText(QString("QGraphicsView::sceneRect=(Left,Top,Width,Height)=%1,%2,%3,%4")
        .arg(rectF.left()).arg(rectF.top()).arg(rectF.width()).arg(rectF.height()));
}

void MainWidget::on_mouseMovePoint(QPoint point)
{
    //鼠标的移动事件，point是GraphicsView的物理坐标
    ui.viewCooridate->setText(QString("View 坐标：%1,%2")
        .arg(point.x()).arg(point.y()));
    //转换到Scene坐标
    QPointF pointScene = ui.graphicsView->mapToScene(point);
    ui.sceneCooridate->setText(QString("Scene 坐标：%1,%2")
        .arg(pointScene.x()).arg(pointScene.y()));
}

void MainWidget::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui.graphicsView->mapToScene(point);
    QGraphicsItem *item = nullptr;
    //获取光标点击的Item
    item = scene->itemAt(pointScene, ui.graphicsView->transform());
    if (item != nullptr)
    {
        //
        QPointF pointItem = item->mapFromScene(pointScene);
        ui.itemCooridate->setText(QString("Item 坐标：%1,%2")
            .arg(pointItem.x()).arg(pointItem.y()));
    }

}

void MainWidget::iniGraphicsSystem()
{
    //左上角坐标，宽度和高度
    QRectF rect(-200, -100, 400, 200);
    scene = new QGraphicsScene(-ui.graphicsView->width() / 2, -ui.graphicsView->height() / 2, ui.graphicsView->width(), ui.graphicsView->height());
    ui.graphicsView->setScene(scene);

    //画一个矩形框与scene尺寸相同
    QGraphicsRectItem *rectItem = new  QGraphicsRectItem(rect);
    rectItem->setFlags(QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);

    QPen pen;
    pen.setWidth(2);
    rectItem->setPen(pen);
    scene->addItem(rectItem);

    //画一个位于scene中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem(-100, -50, 200, 100);
    ellipseItem->setPos(0, 0);
    ellipseItem->setBrush(QBrush(Qt::blue));
    ellipseItem->setFlags(QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(ellipseItem);

    //画一个圆，中心位于scene的边缘
    QGraphicsEllipseItem *ellipseItem2 = new QGraphicsEllipseItem(-50, -50, 100, 100);
    ellipseItem2->setPos(scene->width(), scene->height());
    ellipseItem2->setBrush(QBrush(Qt::red));
    ellipseItem2->setFlags(QGraphicsItem::ItemIsSelectable |
        QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(ellipseItem2);

    scene->clearSelection();
}
