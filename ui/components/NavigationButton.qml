import QtQuick
import QtQuick.Controls


/*!
    \qmltype NavigationButton
    \inherits RoundButton
    \brief Специализированная круглая кнопка для навигации (стрелки "назад"/"вперед").

    Кнопка имеет прозрачный фон в обычном состоянии и подсвечивается акцентным цветом
    при наведении курсора.

    Пример использования:
    \code
    NavigationButton {
        iconPath: "qrc:/icons/back.svg"
        onClicked: myView.goBack()
    }
    \endcode

    \note В компоненте жестко задан \c verticalCenterOffset: 18 для выравнивания
    относительно специфических заголовков приложения.
*/
RoundButton {
    id: btArrow

    /*! \qmlproperty string NavigationButton::iconPath Путь к SVG иконке для отображения внутри кнопки. */
    property string iconPath

    // Конфигурация иконки
    icon.source: iconPath
    icon.color: Theme.textPrimary
    // Слой над остальными элементами
    z: 2
    hoverEnabled: true


    /*
       Эти параметры специфичны для текущего дизайна.
       verticalCenterOffset смещает кнопку чуть ниже центральной линии.
     */
    anchors.verticalCenterOffset: 18
    anchors.leftMargin: 0

    /*! \internal Визуальный стиль фона кнопки */
    background: Rectangle {
        radius: 100
        // Плавная смена цвета при наведении
        color: btArrow.down ? Theme.accentBlue : (btArrow.hovered ? Theme.accentBlue : "transparent")
        opacity: 0.8
    }
}
