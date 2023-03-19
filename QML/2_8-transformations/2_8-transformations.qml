import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML之简单变换")

    MouseArea{
        anchors.fill: parent
        onClicked: {
            image1.y = 10
            image2.rotation = 0
            image3.scale = 1
        }
    }

    ClickableImage{
        id: image1
        x: 10
        y: 10
        source: "../images/pinwheel.png"

        onClicked: {
            y += 10;
        }
    }

    ClickableImage{
        id: image2
        x: image1.x + image1.width + 10
        y: 10
        source: "../images/pinwheel.png"

        onClicked: {
            rotation += 10
        }
    }

    ClickableImage{
        id: image3
        x: image2.x + image2.width + 10
        y: 10
        source: "../images/pinwheel.png"

        onClicked: {
            scale +=0.1
        }
    }
}
