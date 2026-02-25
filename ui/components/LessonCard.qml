import QtQuick
import QtQuick.Layouts

Rectangle {
    id: lessonCard
    radius: 10
    color: Theme.surface
    implicitWidth: 260
    implicitHeight: layoutTexts.implicitHeight + 32

    property string sName: "Основы российской государственности"
    property string lType: "Лекция"
    property string lTime: "09:00 - 10:30"

    ColumnLayout {
        id: layoutTexts
        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        Text {
            id: subjectName
            Layout.fillWidth: true
            text: sName
            wrapMode: Text.WordWrap
            font {
                family: Theme.fontFamily
                pixelSize: Theme.baseSize
            }
            color: Theme.textPrimary
        }

        Text {
            id: lessonType
            text: lType
            font {
                family: Theme.fontFamily
                pixelSize: Theme.fontSizeSmall
            }
            color: Theme.textSecondary
        }

        Text {
            id: lessonTime
            text: lTime
            font {
                family: Theme.fontFamily
                pixelSize: Theme.fontSizeSmall
            }
            color: Theme.accentBlue
        }
    }
}
