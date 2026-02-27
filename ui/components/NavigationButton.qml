import QtQuick
import QtQuick.Controls

RoundButton {
    id: btArrow

    property string iconPath

    icon.source: iconPath
    icon.color: Theme.textPrimary
    z: 2
    hoverEnabled: true
    anchors.verticalCenterOffset: 18
    anchors.leftMargin: 0

    background: Rectangle {
        radius: 100
        color: btArrow.hovered ? Theme.accentBlue : "transparent"
        opacity: 0.8
    }
    font.family: Theme.fontFamily
}
