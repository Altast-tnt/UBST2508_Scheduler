import QtQuick
import QtQuick.Controls

MonthGrid {
    property int currentMonth
    property int currentYear

    RoundButton {
        id: btForwardArrow
        icon.source: "../../assets/icons/arrow.svg"
        icon.color: Theme.textPrimary
        z: 2
        hoverEnabled: true
        anchors.right: parent.right
        anchors.verticalCenter: mainScheduleView.top
        anchors.verticalCenterOffset: 18

        visible: mainScheduleView.contentX < (mainScheduleView.contentWidth
                                              - mainScheduleView.width - 10)

        onClicked: {

            var index = mainScheduleView.indexAt(mainScheduleView.contentX, 0)

            mainScheduleView.positionViewAtIndex(index + 1, ListView.Beginning)
        }

        background: Rectangle {
            radius: 100
            color: btForwardArrow.hovered ? Theme.accentBlue : "transparent"
            opacity: 0.8
        }
        font.family: Theme.fontFamily
        palette.buttonText: Theme.textPrimary
    }
}
