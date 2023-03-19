import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Image的基本使用")

    Image {
        id: image1
        source: "../images/pinwheel.png"
    }

    Image {
        id: image2
        x: image1.x+image1.width+10
        width: image1.width/2
        source: "../images/pinwheel.png"
        //缩放以进行适应尺寸（默认值）
        fillMode: Image.Stretch
    }

    Image {
        id: image3
        x: image2.x+image2.width+10
        width: image1.width/2
        source: "../images/pinwheel.png"
        //必要时进行裁剪
        fillMode: Image.PreserveAspectCrop
        clip: true
    }

    Image {
        id: image4
        x: image3.x+image3.width+10
        width: image1.width/2
        source: "../images/pinwheel.png"
        //不裁剪，按照等比例缩放
        fillMode: Image.PreserveAspectFit
    }
}
