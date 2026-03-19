import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects


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

    Layout.fillWidth: true
    color: Theme.surface
    radius: 5
    implicitHeight: rowLayout.implicitHeight + 20

    /*! \internal Тонкая разделительная линия в нижней части карточки */
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: Theme.textPrimary
        opacity: 0.2
    }

    RowLayout {
        id: rowLayout
        anchors {
            fill: parent
            margins: 10
        }
        spacing: 15

        // Иконка типа файла
        Image {
            source: rootFileCard.fileObj ? rootFileCard.fileObj.icon : ""
            Layout.preferredWidth: Theme.fileIconSize
            Layout.preferredHeight: Theme.fileIconSize
            Layout.alignment: Qt.AlignTop
        }

        // Блок текстовой информации
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignTop
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
                text: !(rootFileCard.fileObj && rootFileCard.fileObj.path
                        !== "") ? "Не скачан" : "Скачано (нажмите открыть)"
                color: !(rootFileCard.fileObj && rootFileCard.fileObj.path
                         !== "") ? Theme.textSecondary : Theme.accentGreen
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                elide: Text.ElideLeft
                Layout.fillWidth: true
            }
        }

        // Блок действий (справа: Кнопка ИЛИ Индикатор)
        Item {
            Layout.alignment: Qt.AlignTop | Qt.AlignRight

            // Фиксируем размер коробки, чтобы верстка не прыгала
            Layout.minimumWidth: Theme.downloadBtnSize
            Layout.minimumHeight: Theme.downloadBtnSize
            Layout.preferredWidth: Theme.downloadBtnSize
            Layout.preferredHeight: Theme.downloadBtnSize

            // Анимация загрузки (крутилка)
            BusyIndicator {
                anchors.fill: parent

                property bool isLoading: rootFileCard.fileObj ? rootFileCard.fileObj.isDownloading : false
                running: isLoading
                visible: isLoading

                // --- Цвета ---
                palette.dark: Theme.textPrimary
                palette.highlight: Theme.textPrimary
                palette.text: Theme.textPrimary
                Material.accent: Theme.accentBlue
            }

            // Кнопка скачивания / открытия
            Image {
                id: iconImage
                anchors.fill: parent

                property bool isLoading: rootFileCard.fileObj ? rootFileCard.fileObj.isDownloading : false
                visible: !isLoading

                source: (rootFileCard.fileObj
                         && rootFileCard.fileObj.path === "") ? "../../assets/icons/download.svg" : "../../assets/icons/openFile.svg"

                sourceSize.width: Theme.downloadBtnSize
                sourceSize.height: Theme.downloadBtnSize

                layer.enabled: true
                layer.effect: ColorOverlay {
                    id: colorOverlay

                    color: Theme.textPrimary
                }

                // Полупрозрачность при наведении
                opacity: dlMouseArea.containsMouse ? 0.7 : 1.0
                MouseArea {
                    id: dlMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: !parent.isLoading
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        if (!rootFileCard.fileObj)
                            return

                        let currentPath = rootFileCard.fileObj.path

                        if (currentPath === "") {
                            appcore.downloadFile(rootFileCard.fileObj)
                        } else {
                            if (currentPath.startsWith("content://")) {
                                // Для Android: отдаем ссылку как есть
                                Qt.openUrlExternally(currentPath)
                            } else {
                                // Для ПК (Linux/Windows/macOS):
                                // Собираем правильный URI без Qt.resolvedUrl.
                                // Если путь уже начинается со слеша (Linux), добавляем 2 слеша.
                                // Если с буквы диска (Windows C:/), добавляем 3 слеша.
                                let prefix = currentPath.startsWith(
                                        "/") ? "file://" : "file:///"
                                Qt.openUrlExternally(prefix + currentPath)
                            }
                        }
                    }
                }
            }
        }
    }
}
