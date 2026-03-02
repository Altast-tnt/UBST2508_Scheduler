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

    MonthGrid {
        id: grid

        Layout.fillWidth: true
        Layout.fillHeight: true

        month: rootLayout.baseDate.getMonth()
        year: rootLayout.baseDate.getFullYear()

        locale: Qt.locale("ru_RU")

        delegate: Rectangle {
            id: dayCell

            // получаем данные для конкретной даты
            property var dayObject: appcore.dayListModel.getDay(model.date)

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
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                    topMargin: 30
                    margins: 4
                }

                spacing: 4
                clip: true
                interactive: false
                // Проверка на существование данных перед биндингом модели
                model: (dayCell.dayObject
                        && dayCell.dayObject.dailyDeadlines) ? dayCell.dayObject.dailyDeadlines : null
                delegate: Rectangle {
                    property var deadlineObj: model.deadlineObject
                    width: ListView.view.width
                    height: 22
                    radius: 6

                    color: (deadlineObj
                            && deadlineObj.isCompleted) ? Theme.accentGreen : Theme.accentRed

                    Text {

                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            right: parent.right
                            margins: 4
                        }

                        text: model.subjectName
                        font.family: Theme.fontFamily
                        font.pixelSize: Theme.fontSizeSmall
                        color: Theme.textPrimary
                        elide: Text.ElideRight
                    }
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


    /*!
        \internal
        Окно с подробным списком дедлайнов для выбранного дня.
        Вызывается при клике на ячейку календаря.
    */
    BasePopup {
        id: detailsPopup
        title: dateTitle

        // Модель данных для ListView внутри попапа
        property var currentModel: null
        // Заголовок даты в формате "1 Марта 2026"
        property string dateTitle: ""

        ListView {
            id: popupList
            Layout.fillWidth: true
            Layout.fillHeight: true
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
                source: "../../assets/images/noDeadline.gif"
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
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }
}
