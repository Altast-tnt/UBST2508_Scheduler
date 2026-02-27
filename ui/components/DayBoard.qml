import QtQuick
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

    NavigationButton {
        id: btBackArrow
        iconPath: "../../assets/icons/back.svg"

        anchors.left: parent.left
        anchors.verticalCenter: mainScheduleView.top
        visible: mainScheduleView.contentX > 10
        onClicked: {

            var index = mainScheduleView.indexAt(mainScheduleView.contentX, 0)
            if (index > 0) {

                mainScheduleView.positionViewAtIndex(index - 1,
                                                     ListView.Beginning)
            }
        }
    }

    NavigationButton {
        id: btForwardArrow

        iconPath: "../../assets/icons/arrow.svg"

        anchors.right: parent.right
        anchors.verticalCenter: mainScheduleView.top
        visible: mainScheduleView.contentX < (mainScheduleView.contentWidth
                                              - mainScheduleView.width - 10)
        onClicked: {

            var index = mainScheduleView.indexAt(mainScheduleView.contentX, 0)

            mainScheduleView.positionViewAtIndex(index + 1, ListView.Beginning)
        }
    }
}
