import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

/*!
    \qmltype SchedulePage
    \inherits DayBoard
    \brief Главная страница раздела "Расписание".

    Компонент является специализированной версией \l DayBoard, настроенной
    для отображения учебных занятий (пар).

    Особенности реализации:
    \list
        \li Использует роль модели \c "lessonsModelRole" для получения данных о занятиях.
        \li Вычисляет и форматирует временной интервал пары (Начало - Конец).
        \li Использует \l LessonCard в качестве визуального представления занятия.
    \endlist

    \sa DayBoard, LessonCard, DeadlinesPage
*/

DayBoard {
    innerModelRole: "lessonsModelRole"
    // Определяем, как будет выглядеть каждое занятие в списке дня
    cardDelegate: Component {
        LessonCard {
            width: ListView.view.width

            sName: subjectName
            lTime: Qt.formatTime(lessonStartTime,
                                 "hh:mm") + " - " + Qt.formatTime(
                       lessonEndTime, "hh:mm")

            lType: lessonTypeName
        }
    }
}
