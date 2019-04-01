import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }

        Image {
            id: image
            x: 188
            y: 161
            width: 100
            height: 100
            source: "qrc:/qtquickplugin/images/template_image.png"
        }

        TextEdit {
            id: textEdit
            x: 208
            y: 315
            width: 80
            height: 20
            text: qsTr("123")
            font.pixelSize: 12
        }
    }
}
