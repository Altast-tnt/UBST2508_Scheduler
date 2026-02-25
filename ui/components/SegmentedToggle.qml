import QtQuick
import QtQuick.Layouts

Rectangle {
    id: segmentedToggle
    radius: 40
    color: "transparent"
    // TODO: протестировать потом размерность на разных устройствах
    implicitWidth: 340
    implicitHeight: textLessons.implicitHeight + 15
    border.color: Theme.accentBlue
    border.width: 1

    property int currentIndex: 0

    RowLayout {
        id: layoutButtons
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: buttonLessons
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 40
            color: (segmentedToggle.currentIndex === 0) ? Theme.accentBlue : "transparent"
            Text {
                id: textLessons

                anchors.centerIn: parent
                text: "Расписание"
                font {
                    family: Theme.fontFamily
                    pixelSize: Theme.baseSize
                }
                color: Theme.textPrimary
            }

            MouseArea {
                id: mouseAreaLessons
                anchors.fill: parent

                onClicked: {
                    currentIndex = 0
                }
            }
        }

        Rectangle {
            id: buttonDeadlines
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: (segmentedToggle.currentIndex === 1) ? Theme.accentBlue : "transparent"
            radius: 40
            Text {
                id: textDeadlines

                anchors.centerIn: parent
                text: "Дедлайны"
                font {
                    family: Theme.fontFamily
                    pixelSize: Theme.baseSize
                }
                color: Theme.textPrimary
            }
            MouseArea {
                id: mouseAreaDeadlines
                anchors.fill: parent

                onClicked: {
                    currentIndex = 1
                }
            }
        }
    }
}
