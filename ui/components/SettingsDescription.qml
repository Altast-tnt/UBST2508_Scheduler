import QtQuick
import QtQuick.Layouts

Text {
    property string description: ""

    text: description
    font.family: Theme.fontFamily
    font.pixelSize: Theme.fontSizeSmall
    color: Theme.textSecondary
    wrapMode: Text.WordWrap
    Layout.fillWidth: true
    horizontalAlignment: Text.AlignHCenter
}
