import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML之键盘输入的基本使用")

    LineEdit{
        id: input1
        text: "Text input 1"
        height: input.font.pixelSize+10
        input.color: "white"
        input.font.pixelSize: 28
        //如果想要直接通过id就能控制焦点，需要将component采用FocusScope进行包裹，详情看Qt文档
        KeyNavigation.tab: input2.input
        input.focus: true
    }

    LineEdit{
        id: input2
        y: input1.y + input1.height + 10
        text: "Text input 2"
        height: input.font.pixelSize+10
        input.color: "white"
        input.font.pixelSize: 28
        KeyNavigation.tab: input1.input
    }
}
