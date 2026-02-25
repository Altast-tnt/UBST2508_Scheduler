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
        Item {
            Layout.fillHeight: true
        }
    }
}
