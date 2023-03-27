import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 800
    height: 480
    title: qsTr("QML之动画的基本使用")

    property bool running: false

    Image{
        id: background
        source: "../images/background.png"
        anchors.fill: parent
    }

    Image {
        id: wheel
        source: "../images/pinwheel.png"
        anchors.verticalCenter: parent.verticalCenter

        NumberAnimation on x{
            to: root.width - wheel.width
            duration: 2000
            running: root.running
        }

        RotationAnimation on rotation {
            to: 360*2
            duration: 2000
            running: root.running
        }
    }

    //PropertyAnimation属于基类，如果有针对性的动画，如RotationAnimation，则最好选择对应的针对性动画
    PropertyAnimation on opacity {
        target: wheel   //如果动画时单独编写的，则需要指定target
        to: 0
        duration: 2000
        running: root.running
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            root.running = true
        }
    }
}
