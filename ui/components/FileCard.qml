import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


/*!
    \qmltype FileCard
    \inherits Rectangle
    \brief Карточка отдельного файла в списке приложений к дедлайну.

    Компонент отображает иконку типа файла, его название, путь/источник
    и кнопку для скачивания.

    Обычно используется в качестве делегата для \c ListView.

    Зависимости:
    \list
        \li \c Theme - для консистентного отображения цветов и шрифтов.
    \endlist
*/
Rectangle {
    id: rootFileCard

    property var fileObj: null

    implicitHeight: Theme.fileCardHeight
    color: Theme.surface
    radius: 5

    /*! \internal Тонкая разделительная линия в нижней части карточки */
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: Theme.textPrimary
        opacity: 0.2
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15

        // Анимация загрузки (крутилка)
        BusyIndicator {
            property bool isLoading: rootFileCard.fileObj ? rootFileCard.fileObj.isDownloading : false

            palette.dark: Theme.textPrimary // Для стиля Basic
            palette.highlight: Theme.textPrimary // Для стиля Fusion / Windows
            palette.text: Theme.textPrimary // Для некоторых других стилей

            Layout.fillWidth: true
            height: Theme.downloadBtnSize
            width: Theme.downloadBtnSize
            running: isLoading
            visible: isLoading
        }

        // Иконка типа файла
        Image {
            source: rootFileCard.fileObj ? rootFileCard.fileObj.icon : ""


            /*
               TODO: Рассмотреть использование Screen.devicePixelRatio
               или адаптивных единиц для размеров иконок.
            */
            Layout.preferredWidth: Theme.fileIconSize
            Layout.preferredHeight: Theme.fileIconSize
            verticalAlignment: Qt.AlignVCenter
        }

        // Блок текстовой информации
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 2

            Text {
                text: rootFileCard.fileObj ? rootFileCard.fileObj.name : ""
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.textPrimary
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Text {
                // Скрываем строку пути, если она пустая
                visible: !!(rootFileCard.fileObj
                            && rootFileCard.fileObj.path !== "")
                text: rootFileCard.fileObj ? rootFileCard.fileObj.path : ""
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.textSecondary
                elide: Text.ElideLeft
                Layout.fillWidth: true
            }
        }

        // Кнопка скачивания
        RoundButton {
            Layout.alignment: Qt.AlignVCenter
            icon.source: (rootFileCard.fileObj
                          && rootFileCard.fileObj.path === "") ? "../../assets/icons/download.svg" : "../../assets/icons/openFile.svg"
            icon.color: Theme.textPrimary
            icon.width: Theme.downloadBtnSize
            icon.height: Theme.downloadBtnSize

            // Прозрачный фон для кнопки
            background: Item {}

            opacity: hovered ? 0.7 : 1.0
            hoverEnabled: true

            property bool isLoading: rootFileCard.fileObj ? rootFileCard.fileObj.isDownloading : false

            // Прячем кнопку, пока идет загрузка
            visible: !isLoading

            onClicked: {
                if (!rootFileCard.fileObj)
                    return

                if (rootFileCard.fileObj.path === "") {
                    appcore.downloadFile(rootFileCard.fileObj)
                } else {
                    // Чтобы файл открылся в системной программе (Word, PDF Reader)
                    Qt.openUrlExternally("file://" + rootFileCard.fileObj.path)
                }
            }
        }
    }
}
