import QtQuick
import QtQuick.Layouts


/*!
    \qmltype DeadlineCard
    \inherits Rectangle
    \brief Визуальная карточка для отображения краткой информации о дедлайне.

    Карточка отображает название предмета, тип работы, время выполнения и
    цветовой индикатор статуса (выполнено/не выполнено).

    При клике на карточку происходит:
    \list
        \li Установка текущего дедлайна в \c appcore.currentDeadline.
        \li Открытие глобального попапа подробностей \c globalDeadlinePopup.
    \endlist

    Зависимости:
    \list
        \li \c Theme - глобальный объект стилизации.
        \li \c appcore - объект логики (C++), содержащий свойство \c currentDeadline.
        \li \c globalDeadlinePopup - глобально доступный компонент \c Popup.
    \endlist
*/
Rectangle {
    id: deadlineCard
    radius: Theme.cardsRadius
    // Интерактивная смена фона при наведении
    color: (cardMouseArea.containsMouse) ? Theme.background : Theme.surface
    implicitWidth: Theme.cardsWidth
    implicitHeight: layoutTexts.implicitHeight + 32

    /*! \qmlproperty string DeadlineCard::sName Название учебного предмета. */
    property string sName: "Основы российской государственности"

    /*! \qmlproperty string DeadlineCard::dType Тип задания (напр. "Презентация", "Курсовая"). */
    property string dType: "Презентация"

    /*! \qmlproperty string DeadlineCard::dTime Текст со временем дедлайна (напр. "до 09:00"). */
    property string dTime: "до 09:00"


    /*!
        \qmlproperty var DeadlineCard::deadlineObj
        Ссылка на объект данных дедлайна из модели.
        Используется для получения статуса завершенности (\c isCompleted).
    */
    property var deadlineObj: model.deadlineObject

    ColumnLayout {
        id: layoutTexts
        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        // Название предмета и индикатор статуса
        RowLayout {
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

            /*! \internal Индикатор статуса: зеленый - выполнено, красный - просрочено/в процессе. */
            Rectangle {
                id: indicator
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                radius: 100
                implicitHeight: Theme.headerButtonSize * 0.4
                implicitWidth: Theme.headerButtonSize * 0.4
                color: (deadlineObj
                        && deadlineObj.isCompleted) ? Theme.accentGreen : Theme.accentRed
            }
        }

        // Подзаголовок: тип дедлайна
        Text {
            id: deadlineType
            text: dType
            font {
                family: Theme.fontFamily
                pixelSize: Theme.fontSizeSmall
            }
            color: Theme.textSecondary
        }

        // Время дедлайна (выделено акцентным цветом)
        Text {
            id: deadlineTime
            text: dTime
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
            // Передаем данные в логику приложения для отображения подробностей
            appcore.currentDeadline = model.deadlineObject
            // Вызываем глобальный попап
            globalDeadlinePopup.open()
        }
    }
}
