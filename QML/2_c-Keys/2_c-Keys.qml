import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML之Keys的基本使用")

    Rectangle{
        id: rect1
        width: 100
        height: 100
        color: "green"
        border.color: Qt.lighter(color)
        focus: true

        Keys.onLeftPressed: rect1.x -= 8
        Keys.onRightPressed: rect1.x += 8
        Keys.onUpPressed: rect1.y -= 8
        Keys.onDownPressed: rect1.y += 8
        Keys.onPressed: function(event){
            switch(event.key){
            case Qt.Key_Plus:
                rect1.scale += 0.2;
                break;
            case Qt.Key_Minus:
                rect1.scale -= 0.2;
                break;
            }
        }
    }
}
