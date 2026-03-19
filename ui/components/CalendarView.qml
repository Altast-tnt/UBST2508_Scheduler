import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


/*!
    \qmltype CalendarView
    \inherits ColumnLayout
    \brief Компонент календаря для отображения и выбора дедлайнов.

    Этот компонент отображает сетку месяца, позволяет переключаться между месяцами
    и просматривать список задач (дедлайнов) на конкретный день во всплывающем окне.

    Требует наличия глобальных объектов:
    \list
        \li \c Theme - объект с настройками цветов и шрифтов.
        \li \c appcore.dayListModel - C++ модель для получения данных о днях.
    \endlist
*/
ColumnLayout {
    id: rootLayout

    Layout.fillWidth: true
    Layout.fillHeight: true

    spacing: 10


    /*!
        \qmlproperty date CalendarView::baseDate
        Дата, определяющая текущий отображаемый месяц. Изменяется при навигации.
    */
    property date baseDate: new Date()


    /*!
        \qmlproperty list<string> CalendarView::monthNames
        Массив локализованных названий месяцев.
    */
    property var monthNames: ["Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"]

    RowLayout {
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter
        spacing: 20

        NavigationButton {
            iconPath: "../../assets/icons/back.svg"
            onClicked: {
                rootLayout.baseDate = new Date(rootLayout.baseDate.getFullYear(
                                                   ),
                                               rootLayout.baseDate.getMonth(
                                                   ) - 1, 1)
            }
        }

        Text {
            text: rootLayout.monthNames[rootLayout.baseDate.getMonth(
                                            )] + " " + rootLayout.baseDate.getFullYear()
            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeLarge
            font.capitalization: Font.Capitalize
            color: Theme.textPrimary
        }

        NavigationButton {
            iconPath: "../../assets/icons/arrow.svg"
            onClicked: {
                rootLayout.baseDate = new Date(rootLayout.baseDate.getFullYear(
                                                   ),
                                               rootLayout.baseDate.getMonth(
                                                   ) + 1, 1)
            }
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: "transparent"

        Flickable {

            id: flickable
            anchors.fill: parent
            contentHeight: grid.height + 50
            clip: true

            MonthGrid {
                id: grid
                width: flickable.width
                height: 350

                month: rootLayout.baseDate.getMonth()
                year: rootLayout.baseDate.getFullYear()

                locale: Qt.locale("ru_RU")

                delegate: Rectangle {
                    id: dayCell

                    // получаем данные для конкретной даты
                    property var dayObject: appcore.dayListModel.getDay(
                                                model.date)

                    color: cellMouseArea.containsMouse ? Theme.accentBlue : Theme.surface

                    border.width: 1
                    border.color: Theme.textSecondary
                    radius: 4

                    Text {
                        anchors {
                            left: parent.left
                            top: parent.top
                            margins: 8
                        }
                        text: model.day
                        font.family: Theme.fontFamily
                        font.pixelSize: Theme.fontSizeSmall
                        color: model.month === grid.month ? Theme.textPrimary : Theme.textSecondary
                        opacity: model.month === grid.month ? 1 : 0.5
                        z: 2
                    }

                    // Список дедлайнов внутри ячейки дня
                    ListView {
                        anchors {
                            bottom: parent.bottom
                            left: parent.left
                            right: parent.right

                            margins: 4
                        }
                        z: 5

                        orientation: ListView.Horizontal
                        spacing: 2
                        height: 6
                        Layout.alignment: Qt.AlignHCenter
                        clip: true
                        interactive: false

                        model: (dayCell.dayObject
                                && dayCell.dayObject.dailyDeadlines) ? dayCell.dayObject.dailyDeadlines : null

                        delegate: Rectangle {
                            property var deadlineObj: model.deadlineObject
                            width: 6
                            height: 6
                            radius: 3

                            color: (deadlineObj
                                    && deadlineObj.isCompleted) ? Theme.accentGreen : Theme.accentRed

                            border.color: Theme.textPrimary
                            border.width: 0.5
                        }
                    }

                    Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        border.color: Theme.accentBlue
                        border.width: 2
                        radius: 4
                        visible: model.today
                        z: 1
                    }

                    MouseArea {
                        id: cellMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true

                        onClicked: {
                            // передаем данные из модели в попап
                            detailsPopup.dateTitle = model.date.toLocaleDateString(
                                        Qt.locale("ru_RU"), "d MMMM yyyy")

                            var dayObj = appcore.dayListModel.getDay(model.date)

                            detailsPopup.currentModel = (dayObj) ? dayObj.dailyDeadlines : null

                            detailsPopup.open()
                        }
                    }
                }
            }
        }
    }


    /*!
        \internal
        Окно с подробным списком дедлайнов для выбранного дня.

        \note Теперь использует \l BasePopup, что автоматически обеспечивает
        единый стиль заголовка, разделителя и анимации появления.
    */
    BasePopup {
        id: detailsPopup
        // Используем встроенное свойство базового шаблона для отображения даты
        title: dateTitle

        // Модель данных для ListView внутри попапа
        property var currentModel: null
        // Заголовок даты в формате "1 Марта 2026"
        property string dateTitle: ""

        ListView {
            id: popupList
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
            interactive: false
            clip: true
            spacing: 10

            model: detailsPopup.currentModel

            delegate: DeadlineCard {
                width: popupList.width

                sName: model.subjectName

                dTime: "До " + Qt.formatTime(model.deadlineDateTime, "hh:mm")
                dType: model.deadlineTypeName
            }
            visible: count > 0
        }

        ColumnLayout {
            id: emptyState
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: popupList.count === 0
            spacing: 10

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            AnimatedImage {
                id: noDataGif
                source: "../../assets/images/noDeadline.gif"
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
                playing: detailsPopup.visible && parent.visible
            }

            Text {
                text: "На этот день дедлайнов нет"
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.textSecondary
                Layout.alignment: Qt.AlignHCenter
                Layout.fillHeight: true
            }
        }
    }
}
