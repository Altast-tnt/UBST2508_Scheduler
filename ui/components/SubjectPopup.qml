import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

BasePopup {
    id: subjectPopup
    title: appcore.currentSubject ? appcore.currentSubject.name : ""

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
        color: (deadlinesTextMouseArea.containsMouse) ? Theme.textSecondary : Theme.accentBlue

        MouseArea {
            id: deadlinesTextMouseArea
            hoverEnabled: true
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                subjectPopup.close()
                globalSubjectDeadlinesPopup.open()
            }
        }
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
