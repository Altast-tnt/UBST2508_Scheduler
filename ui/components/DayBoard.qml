import QtQuick
import QtQuick.Layouts


/*!
    \qmltype DayBoard
    \brief Компонент для горизонтального отображения расписания по дням.

    Компонент организует данные из \c appcore.dayListModel в виде горизонтальной ленты.
    Количество одновременно видимых колонок (дней) рассчитывается динамически в зависимости от ширины экрана.

    Особенности:
    \list
        \li Адаптивная верстка (минимум 250px на колонку).
        \li Поддержка вложенных моделей через \l innerModelRole.
        \li Навигация через кнопки стрелочек.
    \endlist

    Пример использования:
    \code
    DayBoard {
        cardDelegate: MyCustomLessonDelegate {}
        innerModelRole: "tasksModel"
    }
    \endcode
*/
Item {
    id: conteinerMain
    Layout.fillWidth: true
    Layout.fillHeight: true


    /*!
        \qmlproperty string ScheduleView::innerModelRole
        Имя роли в основной модели, которая содержит список занятий (вложенную модель).
        По умолчанию используется \c "lessonsModelRole".
    */
    property string innerModelRole: "lessonsModelRole"


    /*!
        \qmlproperty Component ScheduleView::cardDelegate
        Компонент (делегат), который будет отрисовывать каждое отдельное занятие внутри колонки дня.
    */
    property Component cardDelegate


    /*!
        \internal
        Расчет количества колонок, которые физически помещаются на экране.
        Минимальная ширина колонки принята за 250px.
    */
    property int columnsCount: Math.max(
                                   1, Math.floor(
                                       (mainScheduleView.width + mainScheduleView.spacing)
                                       / (250 + mainScheduleView.spacing)))
    // Горизонтальный список дней
    ListView {
        id: mainScheduleView
        anchors.fill: parent
        orientation: ListView.Horizontal
        spacing: 30
        clip: true
        snapMode: ListView.SnapToItem
        // модель дней
        model: appcore.dayListModel

        highlightMoveDuration: 300

        delegate: ColumnLayout {
            id: dayColumn
            // Динамический расчет ширины колонки на основе columnsCount
            width: (mainScheduleView.width - mainScheduleView.spacing
                    * (conteinerMain.columnsCount - 1)) / conteinerMain.columnsCount
            height: mainScheduleView.height

            property var currentDayData: model

            spacing: 15
            // Шапка дня (Дата и день недели)
            Rectangle {
                Layout.alignment: Qt.AlignHCenter
                implicitWidth: textDay.implicitWidth + 30
                implicitHeight: textDay.implicitHeight + 15
                radius: 20

                border.color: Theme.accentBlue
                border.width: 1
                color: Theme.surface

                Text {
                    id: textDay
                    anchors.centerIn: parent
                    // Ожидается, что в модели есть роль dateStringRole (объект Date)
                    text: dateStringRole.toLocaleDateString(Qt.locale("ru_RU"),
                                                            "dddd dd.MM")
                    font.family: Theme.fontFamily
                    color: Theme.textPrimary
                    font.capitalization: Font.Capitalize
                }
            }
            // Вложенный список занятий внутри конкретного дня
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10
                // Доступ к вложенной модели по динамическому имени роли
                model: dayColumn.currentDayData[conteinerMain.innerModelRole]
                delegate: cardDelegate
            }
        }
    }

    // --- Блок навигации ---

    /*! \internal Кнопка прокрутки к предыдущему дню */
    NavigationButton {
        id: btBackArrow
        iconPath: "../../assets/icons/back.svg"
        anchors.left: parent.left
        anchors.verticalCenter: mainScheduleView.top
        // Скрываем кнопку, если мы в самом начале списка
        visible: mainScheduleView.contentX > 10
        onClicked: {

            var index = mainScheduleView.indexAt(mainScheduleView.contentX, 0)
            if (index > 0) {

                mainScheduleView.positionViewAtIndex(index - 1,
                                                     ListView.Beginning)
            }
        }
    }

    /*! \internal Кнопка прокрутки к следующему дню */
    NavigationButton {
        id: btForwardArrow

        iconPath: "../../assets/icons/arrow.svg"

        anchors.right: parent.right
        anchors.verticalCenter: mainScheduleView.top
        // Скрываем кнопку, если достигнут конец списка
        visible: mainScheduleView.contentX < (mainScheduleView.contentWidth
                                              - mainScheduleView.width - 10)
        onClicked: {

            var index = mainScheduleView.indexAt(mainScheduleView.contentX, 0)

            mainScheduleView.positionViewAtIndex(index + 1, ListView.Beginning)
        }
    }
}
