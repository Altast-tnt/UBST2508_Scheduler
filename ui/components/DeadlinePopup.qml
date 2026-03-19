import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


/*!
    \qmltype DeadlinePopup
    \inherits BasePopup
    \brief Окно подробной информации о дедлайне, построенное на базе \l BasePopup.

    Этот компонент является конкретной реализацией всплывающего окна.
    Он автоматически подтягивает данные из глобального объекта \c appcore:
    \list
        \li Заголовок окна -> \c appcore.currentSubject.name
        \li Контент -> Подробности из \c appcore.currentDeadline
        \li Файлы -> Модель \c appcore.fileModel
    \endlist

    \note Благодаря наследованию от \l BasePopup, весь контент (Email, описание, файлы)
    автоматически компонуется вертикально с заданными отступами.
*/
BasePopup {
    id: deadlinePopup
    // Передаем название предмета напрямую в свойство заголовка базового шаблона
    title: appcore.currentSubject ? appcore.currentSubject.name : ""

    // Блок Email преподавателя
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
            id: emailText
            /*! \internal Логика извлечения email первого преподавателя из списка предмета */
            property var teacher: (appcore.currentSubject
                                   && appcore.currentSubject.teachers.length
                                   > 0) ? appcore.currentSubject.teachers[0] : null
            text: teacher ? teacher.email : ""
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.accentBlue
            opacity: emailMouseArea.containsMouse ? 0.7 : 1.0

            MouseArea {
                id: emailMouseArea
                hoverEnabled: true
                anchors.fill: parent
                cursorShape: (emailText.teacher) ? Qt.PointingHandCursor : Qt.ArrowCursor
                onClicked: {
                    if (emailText.teacher) {
                        // Копируем
                        appcore.copyToClipboard(emailText.teacher.email)

                        // Пытаемся открыть почту
                        Qt.openUrlExternally(
                                    "mailto:" + emailText.teacher.email)
                    }
                }
            }
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
                    appcore.saveDeadlineStatus(appcore.currentDeadline)
                }
            }
            text: ""

            /*! \internal Кастомный стиль индикатора CheckBox */
            indicator: Rectangle {
                implicitWidth: Theme.checkBoxSize
                implicitHeight: Theme.checkBoxSize
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

    // Заголовок секции файлов
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
        Layout.preferredHeight: contentHeight
        clip: true
        spacing: 10
        interactive: false

        // Ожидается модель файлов из C++
        model: appcore.deadlineFileModel

        delegate: FileCard {

            width: popupList.width
            fileObj: model.fileObject
        }
        visible: count > 0
    }
}
