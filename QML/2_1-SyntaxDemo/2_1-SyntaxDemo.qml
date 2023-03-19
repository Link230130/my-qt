import QtQuick 2.12
import QtQuick.Window 2.12

/*
  初识QML之基本语法
*/

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML基本语法")
    onHeightChanged: console.log("height:" ,height)

    Rectangle{
        id: root
        width: 200
        height: 200
        anchors.centerIn: parent
        color: "#4a4a4a"
        border.color: 'red'
        border.width: 2
        Image {
            id: image
            x: (root.width-image.width)/2
            source: "../images/pinwheel.png"
        }

        Text {
            id: hello
            text: qsTr("hello")
            //color: "#ffffff"
            font.pixelSize: 30
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            KeyNavigation.tab: thatLabel
            focus: true
            color: focus ? "red":"black"
        }
        Text{
            id: thatLabel
            text: qsTr("thatLabel")
            color: focus ? "red": "black"
            KeyNavigation.tab: hello
        }
    }
}
