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

    /*! \qmlproperty string FileCard::imageSource Ссылка на иконку (превью) типа файла. */
    property string imageSource
    /*! \qmlproperty string FileCard::fName Имя файла для отображения. */
    property string fName
    /*! \qmlproperty string FileCard::fPath Путь к файлу или URL для загрузки. */
    property string fPath

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15

        // Иконка типа файла
        Image {
            source: rootFileCard.imageSource


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
            Layout.fillHeight: true
            spacing: 2

            Text {
                text: rootFileCard.fName
                font.family: Theme.fontFamily
                font.pixelSize: Theme.baseSize
                color: Theme.textPrimary
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Text {
                // Скрываем строку пути, если она пустая
                visible: rootFileCard.fPath !== ""
                text: rootFileCard.fPath
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
            icon.source: rootFileCard.fPath === "" ? "../../assets/icons/download.svg" : "../../assets/icons/openFile.svg"
            icon.color: Theme.textPrimary
            icon.width: Theme.downloadBtnSize
            icon.height: Theme.downloadBtnSize

            // Прозрачный фон для кнопки
            background: Item {}

            opacity: hovered ? 0.7 : 1.0
            hoverEnabled: true

            onClicked: {
                if (rootFileCard.fPath === "") {
                    appcore.downloadFile(fileObj)
                } else {
                    // Чтобы файл открылся в системной программе (Word, PDF Reader)
                    Qt.openUrlExternally("file://" + rootFileCard.fPath)
                }
            }
        }
    }
}
