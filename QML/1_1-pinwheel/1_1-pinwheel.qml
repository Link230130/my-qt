import QtQuick 2.12
import QtQuick.Window 2.12

/*
 *初识QML之小风车Demo
 */
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("风车转呀转")

    Image {
        anchors.fill: parent    //用当前元素填充parent
        id: background          //id不能修改
        source: "../images/background.png"

        //存在多个对象绘制时，后声明的后绘制
        //支柱
        Image {
            height: parent.height/2
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            id: pole
            source: "../images/pole.png"
        }

        //风车
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            id: pinwheel
            source: "../images/pinwheel.png"

            //为特定的属性修改行为提供动画
            Behavior on rotation{
                NumberAnimation{
                    duration: 500
                }
            }

            //鼠标区域为风车所在区域
            MouseArea{
                anchors.fill: parent
                onClicked: pinwheel.rotation += 360

            }
        }
    }
}
