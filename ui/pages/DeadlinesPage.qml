import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    Layout.fillHeight: true

    spacing: 10

    SegmentedToggle {
        id: segmentedToggle
        Layout.alignment: Qt.AlignHCenter

        firstText: "Список"
        secondText: "Календарь"
        implicitWidth: 230
    }

    StackLayout {
        id: stackLayout

        Layout.fillWidth: true
        Layout.fillHeight: true
        currentIndex: segmentedToggle.currentIndex

        DayBoard {
            innerModelRole: "deadlinesModelRole"
            cardDelegate: Component {
                DeadlineCard {
                    width: ListView.view.width

                    sName: subjectName
                    dTime: "До " + Qt.formatTime(deadlineDateTimeRole,
                                                 "hh:mm") + " - Подробнее"

                    dType: {
                        if (deadlineTypesRole === 0)
                            return "Практика"
                        if (deadlineTypesRole === 1)
                            return "Контрольная"
                        if (deadlineTypesRole === 2)
                            return "Презентация"
                        return "Задание"
                    }
                    isCompleted: deadlineIsCompletedRole
                }
            }
        }

        CalendarView {}
    }
}
