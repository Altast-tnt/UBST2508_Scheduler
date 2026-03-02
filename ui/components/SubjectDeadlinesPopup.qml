import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

BasePopup {
    id: subjectPopup
    title: "Дедлайны: " + appcore.currentSubject ? appcore.currentSubject.name : ""

    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        clip: true
        spacing: 10

        model: appcore.subjectDeadlinesModel

        section.property: "deadlineDateOnly"
        section.criteria: ViewSection.FullString

        section.delegate: Rectangle {
            width: listView.width
            height: 40
            color: "transparent"

            Rectangle {
                anchors.centerIn: parent
                width: dateText.implicitWidth + 30
                height: 30
                radius: 20
                color: Theme.surface
                border.color: Theme.accentBlue

                Text {
                    id: dateText
                    anchors.centerIn: parent
                    text: {
                        var d = new Date(section)
                        return d.toLocaleDateString(Qt.locale("ru_RU"),
                                                    "dddd dd.MM")
                    }
                    font.family: Theme.fontFamily
                    color: Theme.textPrimary
                    font.capitalization: Font.Capitalize
                }
            }
        }

        delegate: DeadlineCard {
            width: ListView.view.width

            sName: model.subjectName
            dTime: "До " + Qt.formatTime(model.deadlineDateTime, "hh:mm")
            dType: model.deadlineTypeName

            property var deadlineObj: model.deadlineObject
        }
    }
}
