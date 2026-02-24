import QtQuick
import QtQuick.Controls

Window {
    id: rootWindow
    width: 1200
    height: 720

    minimumWidth: 640
    minimumHeight: 480

    visible: true
    title: "Проверка"

    Component.onCompleted: {
        Theme.baseSize = (width < 600) ? 14 : 16
    }

    // TODO: при дальнейшей верстке протестировать на разных экранах и подобрать значения
    onWidthChanged: {
        Theme.baseSize = (width < 600) ? 14 : 16
    }

    FontLoader {
        id: fontInterMedium
        source: "assets/fonts/Inter_24pt-Medium.ttf"
        onStatusChanged: {
            console.log("Font status:", status)
            if (status === FontLoader.Ready) {
                Theme.fontFamily = fontInterMedium.name
                console.log("Font status:", status)
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            id: data
            text: "Данные из C++:"
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {

            text: appcore.currentSubject ? appcore.currentSubject.name : "Нет данных"

            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeLarge
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
