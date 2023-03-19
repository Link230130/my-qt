import QtQuick 2.0

Rectangle{
    width: 200
    height: 30
    color: "lightsteelblue"
    border.color: "gray"
    property alias text: input.text
    property alias input: input

    TextInput{
        id: input
        anchors.fill: parent
        anchors.margins: 2
    }
}
