import QtQuick 2.0

Rectangle {
    property alias text: label.text
    width: 50
    height: 50
    color: "blue"
    border.color: Qt.lighter(color)
    Text {
        id: label
        text: qsTr("text")
        color: "white"
        anchors.centerIn: parent
    }
}
