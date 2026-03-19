import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


/*!
    \qmltype SubjectDeadlinesPopup
    \inherits BasePopup
    \brief Окно со списком всех дедлайнов по конкретному предмету.

    Окно отображает хронологический список задач, сгруппированных по дням.
    Для группировки используется механизм \c ListView.section.

    Основные возможности:
    \list
        \li Динамический заголовок с названием предмета.
        \li Секции с датами (формат: "понедельник 12.05").
        \li Использование \l DeadlineCard в качестве элементов списка.
    \endlist

    Зависимости:
    \list
        \li \c appcore.currentSubject - текущий выбранный предмет для заголовка.
        \li \c appcore.subjectDeadlinesModel - C++ модель со списком дедлайнов.
    \endlist
*/
BasePopup {
    id: subjectPopup
    title: "Дедлайны: " + (appcore.currentSubject ? appcore.currentSubject.name : "")

    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.preferredHeight: contentHeight
        interactive: false
        clip: true
        spacing: 10

        // Модель данных, специфичная для выбранного предмета
        model: appcore.subjectDeadlinesModel

        // --- Настройка секций (группировка по датам) ---

        /*! \internal Роль модели, по которой происходит группировка (ожидается строка с датой) */
        section.property: "deadlineDateOnly"
        section.criteria: ViewSection.FullString

        /*! \internal Делегат заголовка секции (плашка с датой) */
        section.delegate: Rectangle {
            width: listView.width
            height: Theme.delegateDateRectHeight
            color: "transparent"

            Rectangle {
                anchors.centerIn: parent
                width: dateText.implicitWidth + 30
                height: Theme.dateRectHeight
                radius: Theme.dateBubbleRadius
                color: Theme.surface
                border.color: Theme.accentBlue

                Text {
                    id: dateText
                    anchors.centerIn: parent
                    // Преобразование строки секции обратно в формат даты для локализации
                    text: {
                        var d = new Date(section)
                        return d.toLocaleDateString(Qt.locale("ru_RU"),
                                                    "dddd dd.MM")
                    }
                    font.family: Theme.fontFamily
                    color: Theme.textPrimary
                    font.capitalization: Font.Capitalize
                }
            }
        }

        // --- Делегат задачи ---
        delegate: DeadlineCard {
            width: ListView.view.width

            // Проброс данных из модели в свойства карточки
            sName: model.subjectName
            dTime: "До " + Qt.formatTime(model.deadlineDateTime, "hh:mm")
            dType: model.deadlineTypeName

            // Ссылка на полный объект дедлайна для внутренних нужд карточки
            property var deadlineObj: model.deadlineObject
        }
    }
}
