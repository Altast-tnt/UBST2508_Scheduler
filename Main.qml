import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: "Проверка"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            id: data
            text: "Данные из C++:"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            // Проверяем на null, чтобы не было ошибок при старте
            text: appcore.currentSubject ? appcore.currentSubject.name : "Нет данных"

            font.pixelSize: 24
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
