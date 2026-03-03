import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


/*!
    \qmltype DeadlinesPage
    \inherits ColumnLayout
    \brief Главная страница раздела "Дедлайны".

    Страница предоставляет пользователю два режима просмотра задач:
    \list
        \li \b {Список (DayBoard)} - линейное отображение дедлайнов по дням.
        \li \b {Календарь (CalendarView)} - классическая сетка месяца.
    \endlist

    Переключение между режимами осуществляется с помощью \l SegmentedToggle.

    Используемые компоненты:
    \list
        \li \l SegmentedToggle - переключатель режимов.
        \li \l StackLayout - контейнер для мгновенной смены представлений.
        \li \l DayBoard (ScheduleView) - универсальный контейнер для отображения дней.
        \li \l CalendarView - кастомный календарь.
    \endlist
*/
ColumnLayout {
    Layout.fillWidth: true
    Layout.fillHeight: true

    spacing: 10

    // --- Переключатель режимов ---
    SegmentedToggle {
        id: segmentedToggle
        Layout.alignment: Qt.AlignHCenter

        firstText: "Список"
        secondText: "Календарь"
        implicitWidth: Theme.segmentedToggleWidthSmall
    }

    // --- Контейнер представлений ---
    StackLayout {
        id: stackLayout

        Layout.fillWidth: true
        Layout.fillHeight: true
        // Индекс текущего окна напрямую связан с переключателем
        currentIndex: segmentedToggle.currentIndex


        /*!
            \internal
            Режим "Список": используется компонент DayBoard (логика ScheduleView),
            настроенный специально под роль дедлайнов.
        */
        DayBoard {
            innerModelRole: "deadlinesModelRole"
            // Передаем кастомный делегат карточки дедлайна
            cardDelegate: Component {
                DeadlineCard {
                    width: ListView.view.width

                    sName: subjectName
                    dTime: "До " + Qt.formatTime(deadlineDateTime,
                                                 "hh:mm") + " - Подробнее"

                    dType: deadlineTypeName
                }
            }
        }

        /*! \internal Режим "Календарь": отображение сетки месяца */
        CalendarView {}
    }
}
