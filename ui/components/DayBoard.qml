import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: conteinerMain
    Layout.fillWidth: true
    Layout.fillHeight: true

    property string innerModelRole: "lessonsModelRole"
    property Component cardDelegate

    property int columnsCount: Math.max(
                                   1, Math.floor(
                                       (mainScheduleView.width + mainScheduleView.spacing)
                                       / (250 + mainScheduleView.spacing)))
    ListView {
        id: mainScheduleView
        anchors.fill: parent
        orientation: ListView.Horizontal
        spacing: 30

        clip: true
        snapMode: ListView.SnapToItem
        model: appcore.dayListModel

        highlightMoveDuration: 300

        delegate: ColumnLayout {
            id: dayColumn
            width: (mainScheduleView.width - mainScheduleView.spacing
                    * (conteinerMain.columnsCount - 1)) / conteinerMain.columnsCount
            height: mainScheduleView.height

            property var currentDayData: model

            spacing: 15

            Rectangle {
                Layout.alignment: Qt.AlignHCenter
                implicitWidth: textDay.implicitWidth + 30
                implicitHeight: textDay.implicitHeight + 15
                radius: 20

                border.color: Theme.accentBlue
                border.width: 1
                color: Theme.surface

                Text {
                    id: textDay
                    anchors.centerIn: parent
                    text: dateStringRole.toLocaleDateString(Qt.locale("ru_RU"),
                                                            "dddd dd.MM")
                    font.family: Theme.fontFamily
                    color: Theme.textPrimary
                    font.capitalization: Font.Capitalize
                }
            }

            ListView {

                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true

                spacing: 10
                model: dayColumn.currentDayData[conteinerMain.innerModelRole]
                delegate: cardDelegate
            }
        }
    }

    RoundButton {
        id: btBackArrow
        icon.source: "../../assets/icons/back.svg"
        icon.color: Theme.textPrimary
        z: 2
        hoverEnabled: true
        anchors.left: parent.left
        anchors.verticalCenter: mainScheduleView.top
        anchors.verticalCenterOffset: 18
        anchors.leftMargin: 0

        visible: mainScheduleView.contentX > 10

        onClicked: {

            var index = mainScheduleView.indexAt(mainScheduleView.contentX, 0)
            if (index > 0) {

                mainScheduleView.positionViewAtIndex(index - 1,
                                                     ListView.Beginning)
            }
        }

        background: Rectangle {
            radius: 100
            color: btBackArrow.hovered ? Theme.accentBlue : "transparent"
            opacity: 0.8
        }
        font.family: Theme.fontFamily
    }

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
