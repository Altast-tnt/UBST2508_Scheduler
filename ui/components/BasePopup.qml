import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Popup {
    id: rootPopup
    anchors.centerIn: parent
    width: parent.width * 0.6
    height: parent.height * 0.8

    modal: true
    focus: true

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property string title: ""

    default property alias content: container.data

    background: Rectangle {
        color: Theme.background
        radius: 30
        border.color: Theme.textPrimary
        border.width: 1
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Text {
            text: rootPopup.title
            visible: text !== ""
            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.textPrimary
            Layout.alignment: Qt.AlignHCenter
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: Theme.textSecondary
            opacity: 0.3
            visible: rootPopup.title !== ""
        }

        ColumnLayout {
            id: container
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 15
        }
    }
}
