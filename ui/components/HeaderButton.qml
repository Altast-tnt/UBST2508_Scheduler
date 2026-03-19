import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RoundButton {
    id: rootBt

    property string iconSource: ""

    hoverEnabled: true
    background: Rectangle {
        radius: parent.radius
        color: rootBt.down ? Theme.accentBlue : (rootBt.hovered ? Theme.accentBlue : "transparent")
        border.width: 1
        border.color: Theme.textSecondary
    }

    radius: 100
    Layout.preferredWidth: Theme.headerButtonSize
    Layout.preferredHeight: Theme.headerButtonSize

    icon.source: iconSource
    icon.color: Theme.textPrimary
    icon.width: Theme.headerButtonSize * 0.5
    icon.height: Theme.headerButtonSize * 0.5
}
