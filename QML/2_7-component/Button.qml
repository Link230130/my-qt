import QtQuick 2.0

Item {
    id: root
    //取别名可以将属性开放出去供外界访问，只有最顶层的元素才可以供外界访问
    property alias text: label.text
    signal clicked

    Rectangle{
        id:button
        x:12
        y:12
        width: 116
        height: 26
        color: "lightsteelblue"
        border.color: "slategrey"
        Text {
            id: label
            text: qsTr("Start")
            anchors.centerIn: parent
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                root.clicked()
            }
        }
    }
}
