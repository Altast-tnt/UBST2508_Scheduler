import QtQuick
import QtQuick.Layouts


/*!
    \qmltype LessonCard
    \inherits Rectangle
    \brief Информационная карточка учебного занятия (пары).

    Используется в расписании для отображения краткой информации о предмете,
    типе занятия и времени его проведения.

    При клике на карточку:
    \list
        \li Устанавливает выбранный предмет в \c appcore.currentSubject.
        \li Открывает глобальное окно подробностей предмета \c globalSubjectPopup.
    \endlist

    Зависимости:
    \list
        \li \c Theme - глобальный объект стилей.
        \li \c appcore - C++ синглтон для управления состоянием приложения.
        \li \c globalSubjectPopup - внешний компонент попапа для деталей предмета.
    \endlist
*/
Rectangle {
    id: lessonCard
    radius: 10
    // Эффект выделения при наведении курсора
    color: (cardMouseArea.containsMouse) ? Theme.background : Theme.surface
    implicitWidth: 260
    implicitHeight: layoutTexts.implicitHeight + 32

    /*! \qmlproperty string LessonCard::sName Полное название учебной дисциплины. */
    property string sName: "Основы российской государственности"
    /*! \qmlproperty string LessonCard::lType Тип занятия: "Лекция", "Семинар", "Лабораторная". */
    property string lType: "Лекция"
    /*! \qmlproperty string LessonCard::lTime Временной интервал занятия (напр. "09:00 - 10:30"). */
    property string lTime: "09:00 - 10:30"

    ColumnLayout {
        id: layoutTexts
        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        // Название предмета с поддержкой переноса строк
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

        // Тип занятия
        Text {
            id: lessonType
            text: lType
            font {
                family: Theme.fontFamily
                pixelSize: Theme.fontSizeSmall
            }
            color: Theme.textSecondary
        }

        // Время проведения
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

    MouseArea {
        id: cardMouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            // Сообщаем ядру приложения, какой предмет сейчас выбран
            appcore.currentSubject = model.subjectObject

            // Открываем окно с деталями (преподаватели, почта и т.д.)
            globalSubjectPopup.open()
        }
    }
}
