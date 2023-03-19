import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Text的基本使用")

    Text {
        id: text1
        text: qsTr("The 1st Text demo")
        color: "#303030"
        font.family: "Ubuntu"
        font.pixelSize: 28
    }

    Text {
        id: text2
        y: text1.y+text1.height+20
        width: 200
        //设置超过width后的文本省略效果，可以设置在前、中、后
        elide: Text.ElideRight
        //换行效果，会屏蔽掉省略效果(仅在显示设置了宽度时有效)
        wrapMode: Text.WordWrap
        text: qsTr("The 2nd Text demo, 很长很长的句子")
        color: "#ffffff"
        font.family: "Ubuntu"
        font.pixelSize: 48
        style: Text.Sunken
        styleColor: "#ff4444"
    }
}
