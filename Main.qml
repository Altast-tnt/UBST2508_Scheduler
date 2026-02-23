import QtQuick
import QtQuick.Controls

Window {
    id: rootWindow
    width: 640
    height: 480
    visible: true
    title: "Проверка"

    FontLoader {
        id: fontInterMedium
        source: "assets/fonts/Inter_24pt-Medium.ttf"
    }

    property string mainFont: fontInterMedium.name

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            id: data
            text: "Данные из C++:"
            font.pixelSize: 16
            font.family: rootWindow.mainFont
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {

            text: appcore.currentSubject ? appcore.currentSubject.name : "Нет данных"

            font.pixelSize: 24
            font.family: rootWindow.mainFont
            font.bold: true
            color: "blue"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: "Перезагрузить (Тест)"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: appcore.loadTestData()
        }
    }
}
