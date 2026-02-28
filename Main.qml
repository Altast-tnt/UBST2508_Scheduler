import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// TODO: убрать все элементы в отдельные кастомные модули (особенно те, которые повторяются)
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
        spacing: 20

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
                Layout.preferredWidth: Theme.headerButtonSize
                Layout.preferredHeight: Theme.headerButtonSize

                icon.source: "assets/icons/settings.svg"
                icon.color: Theme.textPrimary
                icon.width: Theme.headerButtonSize * 0.5
                icon.height: Theme.headerButtonSize * 0.5
            }

            Item {
                Layout.fillWidth: true
            }

            SegmentedToggle {
                id: segmentedToggle
                firstText: "Расписание"
                secondText: "Дедлайны"
            }

            Item {
                Layout.fillWidth: true
            }

            RoundButton {
                id: btChangeTheme

                hoverEnabled: true
                background: Rectangle {
                    radius: parent.radius
                    color: btChangeTheme.hovered ? Theme.accentBlue : "transparent"
                    border.width: 1
                    border.color: Theme.textSecondary
                }

                radius: 100
                Layout.preferredWidth: Theme.headerButtonSize
                Layout.preferredHeight: Theme.headerButtonSize

                icon.source: "assets/icons/changeTheme.svg"
                icon.color: Theme.textPrimary
                icon.width: Theme.headerButtonSize * 0.5
                icon.height: Theme.headerButtonSize * 0.5

                onClicked: {
                    Theme.isDark = !Theme.isDark
                }
            }
        }
        StackLayout {
            id: stackLayout
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: segmentedToggle.currentIndex

            SchedulePage {}
            DeadlinesPage {}
        }
    }
    SubjectPopup {
        id: globalSubjectPopup
    }
    DeadlinePopup {
        id: globalDeadlinePopup
    }
}
