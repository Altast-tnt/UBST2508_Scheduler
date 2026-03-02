import QtQuick
import QtQuick.Layouts


/*!
    \qmltype SegmentedToggle
    \inherits Rectangle
    \brief Двухпозиционный переключатель для выбора режима отображения.

    Компонент представляет собой горизонтальный тумблер с двумя кнопками.
    Используется для переключения контекста приложения (например, между списком занятий и списком задач).

    Пример использования:
    \code
    SegmentedToggle {
        firstText: "Занятия"
        secondText: "Дедлайны"
        onCurrentIndexChanged: console.log("Выбран индекс:", currentIndex)
    }
    \endcode
*/
Rectangle {
    id: segmentedToggle
    radius: 40
    color: "transparent"


    /*
       TODO: Протестировать адаптивность границ и текста на экранах с высоким DPI.
       Возможно, стоит заменить border.width на значение из Theme.
    */
    border.color: Theme.accentBlue
    border.width: 1

    /*! \qmlproperty int SegmentedToggle::currentIndex Индекс выбранного элемента (0 или 1). */
    property int currentIndex: 0
    /*! \qmlproperty string SegmentedToggle::firstText Текст на первой (левой) кнопке. */
    property string firstText
    /*! \qmlproperty string SegmentedToggle::secondText Текст на второй (правой) кнопке. */
    property string secondText

    // Автоматический расчет размеров на основе текста, если не заданы явно
    implicitWidth: 340
    implicitHeight: textLessons.implicitHeight + 15

    RowLayout {
        id: layoutButtons
        anchors.fill: parent
        spacing: 0

        // --- Левая кнопка ---
        Rectangle {
            id: buttonLessons
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 40

            // Визуальное выделение активного состояния
            color: (segmentedToggle.currentIndex === 0) ? Theme.accentBlue : "transparent"

            Text {
                id: textLessons

                anchors.centerIn: parent
                text: firstText
                font {
                    family: Theme.fontFamily
                    pixelSize: Theme.baseSize
                }
                color: Theme.textPrimary
            }

            MouseArea {
                id: mouseAreaLessons
                anchors.fill: parent

                onClicked: {
                    currentIndex = 0
                }
            }
        }

        // --- Правая кнопка ---
        Rectangle {
            id: buttonDeadlines
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: (segmentedToggle.currentIndex === 1) ? Theme.accentBlue : "transparent"
            radius: 40
            Text {
                id: textDeadlines

                anchors.centerIn: parent
                text: secondText
                font {
                    family: Theme.fontFamily
                    pixelSize: Theme.baseSize
                }
                color: Theme.textPrimary
            }
            MouseArea {
                id: mouseAreaDeadlines
                anchors.fill: parent

                onClicked: {
                    currentIndex = 1
                }
            }
        }
    }
}
