import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    id: rootLayout

    Layout.fillWidth: true
    Layout.fillHeight: true

    spacing: 10

    property date baseDate: new Date()

    property var monthNames: ["Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"]

    RowLayout {
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter
        spacing: 20

        NavigationButton {
            iconPath: "../../assets/icons/back.svg"
            onClicked: {
                rootLayout.baseDate = new Date(rootLayout.baseDate.getFullYear(
                                                   ),
                                               rootLayout.baseDate.getMonth(
                                                   ) - 1, 1)
            }
        }

        Text {
            text: rootLayout.monthNames[rootLayout.baseDate.getMonth(
                                            )] + " " + rootLayout.baseDate.getFullYear()
            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeLarge
            font.capitalization: Font.Capitalize
            color: Theme.textPrimary
        }

        NavigationButton {
            iconPath: "../../assets/icons/arrow.svg"
            onClicked: {
                rootLayout.baseDate = new Date(rootLayout.baseDate.getFullYear(
                                                   ),
                                               rootLayout.baseDate.getMonth(
                                                   ) + 1, 1)
            }
        }
    }

    MonthGrid {
        id: grid

        Layout.fillWidth: true
        Layout.fillHeight: true

        month: rootLayout.baseDate.getMonth()
        year: rootLayout.baseDate.getFullYear()

        locale: Qt.locale("ru_RU")

        delegate: Rectangle {
            id: dayCell

            property var dayObject: appcore.dayListModel.getDay(model.date)

            color: cellMouseArea.containsMouse ? Theme.accentBlue : Theme.surface

            border.width: 1
            border.color: Theme.textSecondary
            radius: 4

            Text {
                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 8
                }
                text: model.day
                font.family: Theme.fontFamily
                font.pixelSize: Theme.fontSizeSmall
                color: model.month === grid.month ? Theme.textPrimary : Theme.textSecondary
                opacity: model.month === grid.month ? 1 : 0.5
                z: 2
            }

            ListView {
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                    topMargin: 30
                    margins: 4
                }

                spacing: 4
                clip: true
                interactive: false

                model: (dayCell.dayObject
                        && dayCell.dayObject.dailyDeadlines) ? dayCell.dayObject.dailyDeadlines : null
                delegate: Rectangle {
                    width: ListView.view.width
                    height: 22
                    radius: 6

                    color: model.deadlineIsCompletedRole ? Theme.accentGreen : Theme.accentRed

                    Text {

                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            right: parent.right
                            margins: 4
                        }

                        text: model.subjectName
                        font.family: Theme.fontFamily
                        font.pixelSize: Theme.fontSizeSmall
                        color: Theme.textPrimary
                        elide: Text.ElideRight
                    }
                }
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: Theme.accentBlue
                border.width: 2
                radius: 4
                visible: model.today
                z: 1
            }

            MouseArea {
                id: cellMouseArea
                anchors.fill: parent
                hoverEnabled: true

                onClicked: {

                    detailsPopup.dateTitle = model.date.toLocaleDateString(
                                Qt.locale("ru_RU"), "d MMMM yyyy")

                    var dayObj = appcore.dayListModel.getDay(model.date)

                    detailsPopup.currentModel = (dayObj) ? dayObj.dailyDeadlines : null

                    detailsPopup.open()
                }
            }
        }
    }

    Popup {
        id: detailsPopup

        anchors.centerIn: parent
        width: parent.width * 0.6
        height: parent.height * 0.8

        modal: true
        focus: true

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        property var currentModel: null
        property string dateTitle: ""

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
                text: detailsPopup.dateTitle
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
            }

            ListView {
                id: popupList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10

                model: detailsPopup.currentModel

                delegate: DeadlineCard {
                    width: popupList.width

                    sName: model.subjectName

                    dTime: "До " + Qt.formatTime(model.deadlineDateTimeRole,
                                                 "hh:mm")
                    // TODO: Вынести определение enum в текст в отдельный метод класса
                    dType: {
                        if (model.deadlineTypesRole === 0)
                            return "Практика"
                        if (model.deadlineTypesRole === 1)
                            return "Контрольная"
                        if (model.deadlineTypesRole === 2)
                            return "Презентация"
                        return "Задание"
                    }
                    isCompleted: model.deadlineIsCompletedRole
                }
                visible: count > 0
            }

            ColumnLayout {
                id: emptyState
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: popupList.count === 0
                spacing: 10

                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                AnimatedImage {
                    source: "../../assets/images/noDeadline.gif"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignHCenter
                    playing: detailsPopup.visible && parent.visible
                }

                Text {
                    text: "На этот день дедлайнов нет"
                    font.family: Theme.fontFamily
                    font.pixelSize: Theme.baseSize
                    color: Theme.textSecondary
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }
}
