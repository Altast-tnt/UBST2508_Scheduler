import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


/*!
    \qmltype BasePopup
    \inherits Popup
    \brief Универсальный базовый шаблон для всех всплывающих окон в приложении.

    Этот компонент предоставляет общую визуальную структуру: заголовок,
    разделительную линию и область для контента.

    Использование \c default property позволяет вставлять любое содержимое
    напрямую внутрь BasePopup при его объявлении.

    Пример использования:
    \code
    BasePopup {
        title: "Настройки"

        // Это содержимое автоматически попадет в 'container'
        ColumnLayout {
            CheckBox { text: "Включить уведомления" }
            Button { text: "Сохранить" }
        }
    }
    \endcode
*/
Popup {
    id: rootPopup

    // Стандартное позиционирование и размеры
    anchors.centerIn: parent
    width: parent.width * 0.6
    height: parent.height * 0.8

    modal: true
    focus: true

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    /*! \qmlproperty string BasePopup::title Текст заголовка окна. Если пуст, заголовок и линия скрываются. */
    property string title: ""


    /*!
        \qmlproperty list<Item> BasePopup::content
        \readonly
        Свойство по умолчанию. Все дочерние элементы, объявленные внутри BasePopup,
        будут автоматически помещены в основной ColumnLayout (\c container).
    */
    default property alias content: container.data

    background: Rectangle {
        color: Theme.background
        radius: Theme.popupRadius
        border.color: Theme.textPrimary
        border.width: 1
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // Блок заголовка
        Text {
            text: rootPopup.title
            // Автоматическое скрытие, если заголовок не задан
            visible: text !== ""
            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.textPrimary
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
        }

        // Декоративный разделитель
        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: Theme.textSecondary
            opacity: 0.3
            visible: rootPopup.title !== ""
        }


        /*!
            \internal
            Внутренний контейнер, куда пробрасывается контент через алиас.
        */
        ColumnLayout {
            id: container
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 15
        }
    }
}
