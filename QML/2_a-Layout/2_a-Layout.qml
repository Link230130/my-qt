import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("QML之布局的基本使用")

    //    GreenSquare{
    //        anchors.top: parent.top
    //        anchors.left: parent.left
    //        anchors.margins: 8
    //        BlueSquare{
    //            anchors.fill: parent
    //            text: "(1)"
    //            anchors.margins: 8
    //        }
    //    }

    GreenSquare{
        anchors.centerIn: parent
        BlueSquare{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -10
        }
    }
}
