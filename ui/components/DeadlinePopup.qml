import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

BasePopup {
    id: deadlinePopup
    title: appcore.currentSubject ? appcore.currentSubject.name : ""

    RowLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 5
        Text {
            text: "Email: "
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.textSecondary
        }

        Text {
            /*! \internal Логика извлечения email первого преподавателя из списка предмета */
            property var teacher: (appcore.currentSubject
                                   && appcore.currentSubject.teachers.length
                                   > 0) ? appcore.currentSubject.teachers[0] : null
            text: teacher ? teacher.email : ""
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.accentBlue
        }
    }

    // Блок даты дедлайна
    RowLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 5
        Text {
            text: "Дедлайн: "
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.textSecondary
        }

        Text {
            text: appcore.currentDeadline ? Qt.formatDateTime(
                                                appcore.currentDeadline.dateTime,
                                                "hh:mm dd.MM") : ""
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.accentRed
        }
    }

    // Блок статуса выполнения (CheckBox)
    RowLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 5
        Text {
            Layout.alignment: Qt.AlignTop
            text: "Выполнено: "
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.textSecondary
        }

        CheckBox {
            id: control
            Layout.alignment: Qt.AlignTop
            checked: appcore.currentDeadline ? appcore.currentDeadline.isCompleted : false
            // Прямая запись состояния в C++ модель
            onToggled: {
                if (appcore.currentDeadline) {
                    appcore.currentDeadline.isCompleted = checked
                }
            }
            text: ""

            /*! \internal Кастомный стиль индикатора CheckBox */
            indicator: Rectangle {
                implicitWidth: 20
                implicitHeight: 20
                radius: 4
                color: control.checked ? Theme.accentBlue : Theme.surface
                border.color: Theme.textPrimary
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    text: "✔"
                    color: Theme.textPrimary
                    visible: control.checked
                    font.pixelSize: Theme.baseSize
                    font.bold: true
                }
            }
        }
    }

    // Блок описания дедлайна
    RowLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 5
        Text {
            text: "Описание: "
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.textSecondary
            Layout.alignment: Qt.AlignTop
            Layout.topMargin: 10
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            Layout.minimumHeight: description.implicitHeight + 10
            color: Theme.surface
            radius: 5

            Text {
                id: description

                anchors.fill: parent
                anchors.margins: 10
                text: appcore.currentDeadline ? appcore.currentDeadline.description : "Описание отсутствует..."
                font.family: Theme.fontFamily
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.textPrimary
                wrapMode: Text.WordWrap
            }
        }
    }

    Text {
        Layout.fillWidth: true
        text: "Файлы:"
        font.family: Theme.fontFamily
        font.pixelSize: Theme.baseSize
        color: Theme.textPrimary
    }

    // Список прикрепленных файлов
    ListView {
        id: popupList
        Layout.fillWidth: true
        Layout.fillHeight: true
        clip: true
        spacing: 10

        // Ожидается модель файлов из C++
        model: appcore.fileModel

        delegate: FileCard {

            width: popupList.width
            height: 60

            // Роли модели: fileIcon, fileName, filePath
            imageSource: fileIcon
            fName: fileName
            fPath: filePath
        }
        visible: count > 0
    }
}
