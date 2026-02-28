import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

// TODO: Подумать надо ли делать общий шаблон popup
Popup {
    id: rootPopup

    anchors.centerIn: parent
    width: parent.width * 0.6
    height: parent.height * 0.8

    modal: true
    focus: true

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

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
            text: appcore.currentSubject ? appcore.currentSubject.name : ""
            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.textPrimary
        }

        Text {
            id: headerText
            property var teacher: (appcore.currentSubject
                                   && appcore.currentSubject.teachers.length
                                   > 0) ? appcore.currentSubject.teachers[0] : null
            text: "Преподаватель: " + (teacher ? teacher.name : "Не указан")
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.textSecondary
        }

        RowLayout {
            spacing: 5
            Text {
                text: "Email: "
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.textSecondary
            }

            Text {
                text: headerText.teacher ? headerText.teacher.email : ""
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.accentBlue
            }
        }

        Text {
            text: "Дедлайны по предмету"
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.accentBlue
        }

        Text {
            text: "Файлы:"
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.textPrimary
        }

        ListView {
            id: popupList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 10

            model: appcore.fileModel

            delegate: FileCard {

                width: popupList.width
                height: 60

                imageSource: fileIcon
                fName: fileName
                fPath: filePath
            }
            visible: count > 0
        }
    }
}
