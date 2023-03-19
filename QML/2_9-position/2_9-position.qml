import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("QML之定位器的基本使用")

    //    Column{
    //        spacing: 10
    //        anchors.fill: parent
    //        anchors.margins: 20
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //    }

    //    Row{
    //        spacing: 10
    //        anchors.centerIn: parent
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //    }

    //    Grid{
    //        rowSpacing: 10
    //        columnSpacing: 20
    //        anchors.centerIn: parent
    //        rows: 3
    //        columns: 3
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //    }

    //    Flow{
    //        spacing: 10
    //        anchors.fill: parent
    //        anchors.margins: 20
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //        GreenSquare{}
    //        RedSquare{}
    //    }

    property var colorArray: ["#00bde3","#67c111","#ea7025"]
    Grid{
        anchors.centerIn: parent
        anchors.margins: 20
        spacing: 10
        columns: 5//Grid的默认columns为4
        Repeater{
            model: 25

            RedSquare{
                id: rect
                property int colorIndex: Math.floor(Math.random(0,1)*3)
                color: root.colorArray[colorIndex]
                Text {
                    anchors.centerIn: parent
                    id: text
                    text: qsTr("cell" + rect.Positioner.index)
                    color: "white"
                }
            }
        }
    }
}
