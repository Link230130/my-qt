import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("MouseArea的基本使用")

    Rectangle{
        id: rect1
        x:10
        y: 10
        width: 90
        height: 90
        color: "lightsteelblue"

        MouseArea{
            width: parent.width
            height: parent.height
            onClicked: rect2.visible=!rect2.visible
        }
    }

    Rectangle{
        id: rect2
        x:rect1.x + rect1.width + 10
        y:rect1.y
        width: 90
        height: 90
        border.color: "lightsteelblue"
        border.width: 4
        radius: 8
    }
}
