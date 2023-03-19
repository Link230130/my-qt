import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("component组件的基本使用")

    Button{
        text: "开始"
        onClicked: {
            text1.text = "按钮被点击"
        }
    }

    Text {
        id: text1
        text: qsTr("waiting ...")
        x:12
        y:76
        width: 116
        height: 26
        horizontalAlignment: Text.AlignHCenter
    }
}
