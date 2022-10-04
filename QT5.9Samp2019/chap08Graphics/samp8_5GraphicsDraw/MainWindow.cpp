#include "QWGraphicsView.h"
#include "MainWindow.h"
#include <QTime>
#include <QGraphicsEllipseItem>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>

//函数模板
template<class T> void setBrushColor(T *item)
{
    QColor color = item->brush().color();
    color = QColorDialog::getColor(color, NULL, "选择填充颜色");
    if (color.isValid())
    {
        item->setBrush(QBrush(color));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    iniUI();
}

void MainWindow::iniUI()
{
    seqNum = 0;
    frontZ = 0;
    backZ = 0;

    labViewCord = new QLabel("View 坐标: ");
    labViewCord->setMinimumWidth(150);

    labSceneCord = new QLabel("Scene 坐标: ");
    labSceneCord->setMinimumWidth(150);

    labItemCord = new QLabel("Item 坐标: ");
    labItemCord->setMinimumWidth(150);

    labItemInfo = new QLabel("ItemInfo: ");
    labItemInfo->setMinimumWidth(200);

    ui.statusBar->addWidget(labViewCord);
    ui.statusBar->addWidget(labSceneCord);
    ui.statusBar->addWidget(labItemCord);
    ui.statusBar->addWidget(labItemInfo);

    //创建QGraphicsScene
    scene = new QGraphicsScene(-300, -200, 600, 400);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->setCursor(Qt::CrossCursor);
    ui.graphicsView->setMouseTracking(true);
    ui.graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    this->setCentralWidget(ui.graphicsView);

    ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(ui.graphicsView, &QWGraphicsView::mouseMovePoint, this, &MainWindow::on_mouseMovePoint);
    connect(ui.graphicsView, &QWGraphicsView::mouseClicked, this, &MainWindow::on_mouseClicked);
    connect(ui.graphicsView, &QWGraphicsView::mouseDoubleClick, this, &MainWindow::on_mouseDoubleClick);
    connect(ui.graphicsView, &QWGraphicsView::keyPress, this, &MainWindow::on_keyPress);

    qsrand(QTime::currentTime().second());
}

//鼠标移动
void MainWindow::on_mouseMovePoint(QPoint point)
{
    labViewCord->setText(QString("View 坐标: %1，%2").arg(point.x()).arg(point.y()));
    QPointF pointScene = ui.graphicsView->mapToScene(point);
    labSceneCord->setText(QString("Scene 坐标: %1,%2").arg(pointScene.x()).arg(pointScene.y()));
}

//鼠标单击
void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui.graphicsView->mapToScene(point);
    QGraphicsItem *item = NULL;
    item = scene->itemAt(pointScene, ui.graphicsView->transform());
    if (item != NULL)
    {
        QPointF pointItem = item->mapFromScene(pointScene);
        labItemCord->setText(QString("Item 坐标: %1,%2").arg(pointItem.x()).arg(pointItem.y()));
        labItemInfo->setText(item->data(ItemDesciption).toString() + ", ItemId= "
            + item->data(ItemId).toString());
    }
}

void MainWindow::on_mouseDoubleClick(QPoint point)
{
    QPointF pointScene = ui.graphicsView->mapToScene(point);
    QGraphicsItem *item = NULL;
    item = scene->itemAt(pointScene, ui.graphicsView->transform());
    if (item == NULL)
    {
        return;
    }
    switch (item->type())
    {
    case QGraphicsRectItem::Type:
    {
        QGraphicsRectItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
        setBrushColor(theItem);
        break;
    }
    case QGraphicsEllipseItem::Type:
    {
        QGraphicsEllipseItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        setBrushColor(theItem);
        break;
    }
    case QGraphicsPolygonItem::Type:
    {

        break;
    }
    case QGraphicsLineItem::Type:
    {
        QGraphicsLineItem* theItem;
        theItem = qgraphicsitem_cast<QGraphicsLineItem*>(item);
        QPen pen = theItem->pen();
        QColor color = theItem->pen().color();
        color = QColorDialog::getColor(color, this, "选择线条颜色");
        if (color.isValid())
        {
            pen.setColor(color);
            theItem->setPen(pen);
        }
        break;
    }
    case QGraphicsTextItem::Type:
    {
        QGraphicsTextItem *theItem;
        theItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);
        QFont font = theItem->font();
        bool ok = false;
        font = QFontDialog::getFont(&ok, font, this, "设置字体");
        if (ok)
        {
            theItem->setFont(font);
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_keyPress(QKeyEvent * event)
{
    if (scene->selectedItems().count() != 1)
    {
        return;
    }
    QGraphicsItem *item = scene->selectedItems().at(0);
    if (event->key() == Qt::Key_Delete)
    {
        scene->removeItem(item);
    }
    else if (event->key() == Qt::Key_Space)
    {
        item->setRotation(90 + item->rotation());
    }
    else if (event->key() == Qt::Key_Left)
    {
        item->setX(-1 + item->x());
    }
    else if (event->key() == Qt::Key_Right)
    {
        item->setX(1 + item->x());
    }
    else if (event->key() == Qt::Key_Up)
    {
        item->setY(-1 + item->y());
    }
    else if (event->key() == Qt::Key_Down)
    {
        item->setY(1 + item->y());
    }
}

void MainWindow::on_actItem_Rect_triggered()
{
}

//添加椭圆
void MainWindow::on_actItem_Ellipse_triggered()
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(-50, -30, 100, 60);
    item->setFlags(QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::blue));
    //用于叠放顺序
    item->setZValue(++frontZ);
    //初始位置
    item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));
    //自定义数据1：ItemId为key；自定义数据2：ItemDesciption为key
    item->setData(ItemId, ++seqNum);
    item->setData(ItemDesciption, "椭圆");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void MainWindow::on_actItem_Polygon_triggered()
{
}

//删除选中的图形项
void MainWindow::on_actEdit_Delete_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt > 0)
    {
        for (int i = 0; i < cnt; i++)
        {
            QGraphicsItem *item = scene->selectedItems().at(0);
            scene->removeItem(item);
        }
    }
}

//放大
void MainWindow::on_actZoomIn_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setScale(0.1 + item->scale());
    }
    else
    {
        ui.graphicsView->scale(1.1, 1.1);
    }
}

//缩小
void MainWindow::on_actZoomOut_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setScale(item->scale() - 0.1);
    }
    else
    {
        ui.graphicsView->scale(0.9, 0.9);
    }
}

//恢复坐标系统变换
void MainWindow::on_actRestore_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        //item->resetTransform(); //不起作用，无法恢复
        item->setRotation(0);
        item->setScale(1.0);
    }
    else
    {
        ui.graphicsView->resetTransform();
    }
}

//逆时针旋转
void MainWindow::on_actRotateLeft_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setRotation(-30 + item->rotation());
    }
    else
    {
        ui.graphicsView->rotate(-30);
    }
}

//顺时针旋转
void MainWindow::on_actRotateRight_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setRotation(30 + item->rotation());
    }
    else
    {
        ui.graphicsView->rotate(30);
    }
}

//前置
void MainWindow::on_actEdit_Front_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setZValue(++frontZ);
    }
}

//后置
void MainWindow::on_actEdit_Back_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setZValue(--backZ);
    }
}

void MainWindow::on_actItem_Line_triggered()
{
}

//添加文字
void MainWindow::on_actItem_Text_triggered()
{
    QString str = QInputDialog::getText(this, "输入文字", "请输入文字");
    if (str.isEmpty())
    {
        return;
    }
    QGraphicsTextItem *item = new QGraphicsTextItem(str);
    QFont font = this->font();
    font.setPointSize(20);
    font.setBold(true);
    item->setFont(font);

    item->setFlags(QGraphicsItem::ItemIsSelectable |
        QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
    item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));
    item->setZValue(++frontZ);

    item->setData(ItemId, ++seqNum);
    item->setData(ItemDesciption, "文本");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

//组合
void MainWindow::on_actGroup_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt > 1)
    {
        QGraphicsItemGroup *group = new QGraphicsItemGroup;
        scene->addItem(group);
        for (int i = 0; i < cnt; ++i)
        {
            QGraphicsItem *item = scene->selectedItems().at(0);
            item->setSelected(false);//清除虚线框
            item->clearFocus();
            group->addToGroup(item);
        }
        group->setFlags(QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        group->setZValue(++frontZ);
        scene->clearSelection();
        group->setSelected(true);
    }
}

//取消组合
void MainWindow::on_actGroupBreak_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItemGroup *group;
        group = (QGraphicsItemGroup*)scene->selectedItems().at(0);
        scene->destroyItemGroup(group);
    }
}

void MainWindow::on_actItem_Circle_triggered()
{
}

void MainWindow::on_actItem_Triangle_triggered()
{
}
