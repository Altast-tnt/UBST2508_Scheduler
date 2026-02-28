import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

DayBoard {
    innerModelRole: "lessonsModelRole"
    cardDelegate: Component {
        LessonCard {
            width: ListView.view.width

            sName: subjectName
            lTime: Qt.formatTime(lessonStartTime,
                                 "hh:mm") + " - " + Qt.formatTime(
                       lessonEndTime, "hh:mm")

            lType: lessonTypeName
        }
    }
}
