import QtQuick
import QtQuick.Layouts

Rectangle {
    id: deadlineCard
    radius: 10
    color: (cardMouseArea.containsMouse) ? Theme.background : Theme.surface
    implicitWidth: 260
    implicitHeight: layoutTexts.implicitHeight + 32

    property string sName: "Основы российской государственности"
    property string dType: "Презентация"
    property string dTime: "до 09:00"
    property var deadlineObj: model.deadlineObject

    ColumnLayout {
        id: layoutTexts
        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        RowLayout {
            Text {
                id: subjectName
                Layout.fillWidth: true
                text: sName
                wrapMode: Text.WordWrap
                font {
                    family: Theme.fontFamily
                    pixelSize: Theme.baseSize
                }
                color: Theme.textPrimary
            }
            Rectangle {
                id: indicator
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                radius: 100
                implicitHeight: Theme.headerButtonSize * 0.4
                implicitWidth: Theme.headerButtonSize * 0.4
                color: (deadlineObj
                        && deadlineObj.isCompleted) ? Theme.accentGreen : Theme.accentRed
            }
        }

        Text {
            id: deadlineType
            text: dType
            font {
                family: Theme.fontFamily
                pixelSize: Theme.fontSizeSmall
            }
            color: Theme.textSecondary
        }

        Text {
            id: deadlineTime
            text: dTime
            font {
                family: Theme.fontFamily
                pixelSize: Theme.fontSizeSmall
            }
            color: Theme.accentBlue
        }
    }

    MouseArea {
        id: cardMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            appcore.currentDeadline = model.deadlineObject

            globalDeadlinePopup.open()
        }
    }
}
