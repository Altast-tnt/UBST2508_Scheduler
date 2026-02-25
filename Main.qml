import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: rootWindow
    width: 1200
    height: 720

    minimumWidth: 640
    minimumHeight: 480

    visible: true
    color: Theme.background
    title: "Проверка"

    Component.onCompleted: {
        Theme.baseSize = (width < 600) ? 14 : 16
    }

    // TODO: при дальнейшей верстке протестировать на разных экранах и подобрать значения
    onWidthChanged: {
        Theme.baseSize = (width < 600) ? 14 : 16
    }

    FontLoader {
        id: fontInterMedium
        source: "assets/fonts/Inter_24pt-Medium.ttf"
        onStatusChanged: {
            console.log("Font status:", status)
            if (status === FontLoader.Ready) {
                Theme.fontFamily = fontInterMedium.name
                console.log("Font status:", status)
            }
        }
    }

    ColumnLayout {
        id: mainContainer

        anchors.fill: parent
        anchors.margins: 40
        spacing: 40

        RowLayout {
            id: header
            Layout.fillHeight: false

            RoundButton {
                id: btSettings

                background: Rectangle {
                    radius: parent.radius
                    color: "transparent"
                    border.width: 1
                    border.color: Theme.textSecondary
                }

                radius: 100
                // TODO: Сделать адаптивный размер кнопок
                width: 50
                height: 50

                icon.source: "assets/icons/settings.svg"
                icon.color: Theme.textPrimary
            }

            Item {
                Layout.fillWidth: true
            }

            SegmentedToggle {
                id: segmentedToggle
            }

            Item {
                Layout.fillWidth: true
            }

            RoundButton {
                id: btChangeTheme

                background: Rectangle {
                    radius: parent.radius
                    color: "transparent"
                    border.width: 1
                    border.color: Theme.textSecondary
                }

                radius: 100
                // TODO: Сделать адаптивный размер кнопок
                width: 50
                height: 50

                icon.source: "assets/icons/changeTheme.svg"
                icon.color: Theme.textPrimary
            }
        }

        ListView {
            id: mainScheduleView
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: ListView.Horizontal
            spacing: 30

            clip: true
            model: appcore.dayListModel

            delegate: ColumnLayout {
                width: (rootWindow.width / 4)
                height: mainScheduleView.height

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
                        text: dateStringRole.toLocaleDateString(
                                  Qt.locale("ru_RU"), "dddd dd.MM")
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
                    model: lessonsModelRole

                    delegate: LessonCard {
                        width: ListView.view.width

                        sName: subjectName
                        lTime: Qt.formatTime(lessonStartTime,
                                             "hh:mm") + " - " + Qt.formatTime(
                                   lessonEndTime, "hh:mm")

                        lType: {
                            if (lessonType === 0)
                                return "Лекция"
                            if (lessonType === 1)
                                return "Практика"
                            if (lessonType === 2)
                                return "Лабораторная"
                            return "Занятие"
                        }
                    }
                }
            }
        }
    }
}
