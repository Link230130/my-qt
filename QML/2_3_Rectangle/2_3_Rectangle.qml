import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Rectangle的基本使用")

    Rectangle{
        id: rect1
        x:12
        y:12
        width: 76
        height: 96
        color: "lightsteelblue"
    }

    Rectangle{
        id: rect2
        x:112
        y:12
        width: 76
        height: 96
        border.color: "lightsteelblue"
        border.width: 4
        radius: 20
    }

    Rectangle{
        id: rect3
        x:212
        y:12
        width: 76
        height: 96
        //渐变色,position为0表示顶部，1表示底部
        gradient: Gradient{
            GradientStop{position: 0.0; color: "lightsteelblue"}
            GradientStop{position: 1.0; color: "slategray"}
        }
        border.color: "lightsteelblue"
        border.width: 4
        radius: 20
    }
}
