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
                    dTime: "До " + Qt.formatTime(deadlineDateTime,
                                                 "hh:mm") + " - Подробнее"

                    dType: deadlineTypeName
                    isCompleted: deadlineIsCompleted
                }
            }
        }

        CalendarView {}
    }
}
