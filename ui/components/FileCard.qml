import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    id: rootFileCard
    implicitHeight: 60
    color: Theme.surface

    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: Theme.textPrimary
        opacity: 0.2
    }

    property string imageSource
    property string fName
    property string fPath

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15

        Image {
            source: rootFileCard.imageSource
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32
            verticalAlignment: Qt.AlignVCenter
        }

        ColumnLayout {
            Layout.fillHeight: true
            spacing: 2

            Text {
                text: rootFileCard.fName
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.textPrimary
                elide: Text.ElideRight
                Layout.fillWidth: true
            }
            Text {
                visible: rootFileCard.fPath !== ""
                text: rootFileCard.fPath
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.textSecondary
                elide: Text.ElideLeft
                Layout.fillWidth: true
            }
        }

        RoundButton {
            Layout.alignment: Qt.AlignVCenter

            icon.source: "../../assets/icons/download.svg"
            icon.color: Theme.textPrimary
            icon.width: 24
            icon.height: 24

            background: Item {}

            opacity: hovered ? 0.7 : 1.0
            hoverEnabled: true

            onClicked: {
                console.log("Скачиваем файл: " + rootFileCard.fName)
            }
        }
    }
}
