import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

RoundButton {
    id: rootBt

    property string buttonText: ""

    text: buttonText

    Layout.fillWidth: true
    radius: 20

    hoverEnabled: true

    contentItem: Text {
        text: rootBt.text
        font.family: Theme.fontFamily
        font.pixelSize: Theme.baseSize

        color: Theme.textPrimary

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        radius: parent.radius
        color: rootBt.down ? Theme.accentBlue : (rootBt.hovered ? Theme.accentBlue : Theme.surface)
        border.width: 1
        border.color: Theme.accentBlue
    }
}
