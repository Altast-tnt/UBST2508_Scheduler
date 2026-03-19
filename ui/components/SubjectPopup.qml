import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


/*!
    \qmltype SubjectPopup
    \inherits BasePopup
    \brief Информационное окно с деталями учебной дисциплины.

    Отображает данные о преподавателе, контактный email и прикрепленные к предмету файлы.
    Также содержит интерактивную ссылку для перехода к списку всех дедлайнов по этому предмету.

    Функционал:
    \list
        \li Автоматическое извлечение данных первого преподавателя из \c currentSubject.
        \li Динамический переход: закрывает текущее окно и открывает \c globalSubjectDeadlinesPopup.
        \li Список файлов предмета через \c FileCard.
    \endlist

    Зависимости:
    \list
        \li \c appcore.currentSubject - объект текущего предмета.
        \li \c appcore.fileModel - модель файлов для данного предмета.
        \li \c globalSubjectDeadlinesPopup - глобальный объект окна со списком задач.
    \endlist
*/
BasePopup {
    id: subjectPopup
    title: appcore.currentSubject ? appcore.currentSubject.name : ""

    // --- Блок информации о преподавателе ---
    Text {
        id: headerText
        /*! \internal Логика получения данных первого преподавателя из массива предмета */
        property var teacher: (appcore.currentSubject
                               && appcore.currentSubject.teachers.length
                               > 0) ? appcore.currentSubject.teachers[0] : null
        text: "Преподаватель: " + (teacher ? teacher.name : "Не указан")
        font.family: Theme.fontFamily
        font.pixelSize: Theme.baseSize
        color: Theme.textSecondary
        Layout.fillWidth: true
        wrapMode: Text.WordWrap
    }

    // Блок Email (использует данные из headerText.teacher)
    RowLayout {
        spacing: 5
        Layout.fillWidth: true
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
            opacity: emailMouseArea.containsMouse ? 0.7 : 1.0

            MouseArea {
                id: emailMouseArea
                hoverEnabled: true
                anchors.fill: parent
                cursorShape: (headerText.teacher) ? Qt.PointingHandCursor : Qt.ArrowCursor
                onClicked: {
                    if (headerText.teacher) {
                        // Копируем
                        appcore.copyToClipboard(headerText.teacher.email)

                        // Пытаемся открыть почту
                        Qt.openUrlExternally(
                                    "mailto:" + headerText.teacher.email)
                    }
                }
            }
        }
    }

    // --- Ссылка на дедлайны ---
    /*! \internal Текстовая ссылка для перехода к списку всех дедлайнов дисциплины */
    Text {
        Layout.fillWidth: true
        text: "Дедлайны по предмету"
        font.family: Theme.fontFamily
        font.pixelSize: Theme.baseSize
        // Визуальный отклик при наведении (Hover)
        color: (deadlinesTextMouseArea.containsMouse) ? Theme.textSecondary : Theme.accentBlue

        MouseArea {
            id: deadlinesTextMouseArea
            hoverEnabled: true
            anchors.fill: parent
            // Указатель "рука" для UX
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                // Логика переключения между попапами
                subjectPopup.close()
                globalSubjectDeadlinesPopup.open()
            }
        }
    }

    // --- Список файлов предмета ---
    Text {
        Layout.fillWidth: true
        text: "Файлы:"
        font.family: Theme.fontFamily
        font.pixelSize: Theme.baseSize
        color: Theme.textPrimary
    }

    ListView {
        id: popupList
        Layout.fillWidth: true
        Layout.preferredHeight: contentHeight
        clip: true
        spacing: 10
        interactive: false

        model: appcore.subjectFileModel

        delegate: FileCard {

            width: popupList.width
            fileObj: model.fileObject
        }
        visible: count > 0
    }
}
