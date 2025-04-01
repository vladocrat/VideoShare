import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PixmapImage

Window {
    width: 1920
    height: 1080 + 25
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

        ComboBox {
            Layout.minimumHeight: 25
            Layout.minimumWidth: 100
            Layout.maximumHeight: 25
            Layout.maximumWidth: 100

            model: enumModel
        }

        PixmapImage {
            Layout.fillWidth: true
            Layout.fillHeight: true

            frame: frameProvider.frame
        }
    }
}
