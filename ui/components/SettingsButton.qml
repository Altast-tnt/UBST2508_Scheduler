import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

RoundButton {
    id: rootBt

    property string buttonText: ""
    text: buttonText
    palette.buttonText: Theme.textPrimary
    font.pixelSize: Theme.baseSize
    font.family: Theme.fontFamily
    Layout.fillWidth: true
    radius: 20

    hoverEnabled: true
    background: Rectangle {
        radius: parent.radius
        color: rootBt.hovered ? Theme.accentBlue : Theme.surface
        border.width: 1
        border.color: Theme.accentBlue
    }
}
