import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


    DayBoard {
        innerModelRole: "deadlinesModelRole"
        cardDelegate: Component {
            DeadlineCard {
                width: ListView.view.width

                sName: subjectName
                dTime: "До " + Qt.formatTime(deadlineDateTimeRole, "hh:mm") + " - Подробнее"

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

