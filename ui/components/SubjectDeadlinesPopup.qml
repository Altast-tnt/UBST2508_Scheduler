import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Popup {
    id: rootPopup
    anchors.centerIn: parent
    width: parent.width * 0.9
    height: parent.height * 0.8
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    background: Rectangle {
        color: Theme.background
        radius: 30
        border.color: Theme.textPrimary
        border.width: 1
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Text {
            text: "Дедлайны: " + (appcore.currentSubject ? appcore.currentSubject.name : "")
            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.textPrimary
            Layout.alignment: Qt.AlignHCenter
            elide: Text.ElideRight
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
        }

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
}
