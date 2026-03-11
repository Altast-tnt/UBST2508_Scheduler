import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


/*!
    \qmltype Main
    \brief Главное окно приложения.

    Здесь происходит:
    \list
        \li Инициализация глобальной темы и шрифтов.
        \li Динамическая подстройка размеров под ширину окна (Responsiveness).
        \li Объявление глобальных попапов, доступных из любой части приложения.
        \li Навигация между основными разделами (Расписание/Дедлайны).
    \endlist
*/
Window {
    id: rootWindow
    width: 1200
    height: 720
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    color: Theme.background
    title: "Проверка"

    /*! \internal Функция для адаптивного изменения базового размера шрифта */
    function updateResponsiveStyles() {
        Theme.baseSize = (width < 600) ? 14 : 16
    }

    Component.onCompleted: updateResponsiveStyles()
    onWidthChanged: updateResponsiveStyles()

    // --- Загрузка ресурсов ---
    FontLoader {
        id: fontInterMedium
        source: "assets/fonts/Inter_24pt-Medium.ttf"
        onStatusChanged: {
            if (status === FontLoader.Ready) {
                Theme.fontFamily = fontInterMedium.name
            } else if (status === FontLoader.Error) {
                console.error("Ошибка загрузки шрифта Inter")
            }
        }
    }

    // --- Основной макет ---
    ColumnLayout {
        id: mainContainer

        anchors.fill: parent
        anchors.margins: 40
        spacing: 20

        // Верхняя панель (Header)
        RowLayout {
            id: header
            Layout.fillHeight: false

            // Кнопка настроек
            RoundButton {
                id: btSettings

                background: Rectangle {
                    radius: parent.radius
                    color: "transparent"
                    border.width: 1
                    border.color: Theme.textSecondary
                }

                radius: 100
                Layout.preferredWidth: Theme.headerButtonSize
                Layout.preferredHeight: Theme.headerButtonSize

                icon.source: "assets/icons/settings.svg"
                icon.color: Theme.textPrimary
                icon.width: Theme.headerButtonSize * 0.5
                icon.height: Theme.headerButtonSize * 0.5
            }

            // Распорка
            Item {
                Layout.fillWidth: true
            }

            // Главный переключатель разделов
            SegmentedToggle {
                id: segmentedToggle
                firstText: "Расписание"
                secondText: "Дедлайны"
            }

            // Распорка
            Item {
                Layout.fillWidth: true
            }

            // Кнопка смены темы (День/Ночь)
            RoundButton {
                id: btChangeTheme

                hoverEnabled: true
                background: Rectangle {
                    radius: parent.radius
                    color: btChangeTheme.hovered ? Theme.accentBlue : "transparent"
                    border.width: 1
                    border.color: Theme.textSecondary
                }

                radius: 100
                Layout.preferredWidth: Theme.headerButtonSize
                Layout.preferredHeight: Theme.headerButtonSize

                icon.source: "assets/icons/changeTheme.svg"
                icon.color: Theme.textPrimary
                icon.width: Theme.headerButtonSize * 0.5
                icon.height: Theme.headerButtonSize * 0.5

                onClicked: {
                    Theme.isDark = !Theme.isDark
                }
            }
        }

        // Основной контент страниц
        StackLayout {
            id: stackLayout
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: segmentedToggle.currentIndex

            SchedulePage {}
            DeadlinesPage {}
        }
    }

    Connections {
        target: appcore
        function onShowNotification(message) {
            toastText.text = message
            toastPopup.open()
            toastTimer.restart()
        }
    }

    // Всплывающее уведомление (если ошибка сети)
    Popup {
        id: toastPopup
        anchors.centerIn: parent

        // Убираем фокус и модальность, чтобы не мешать пользователю кликать
        modal: false
        focus: false
        closePolicy: Popup.NoAutoClose

        background: Rectangle {
            color: Theme.surface
            radius: 10
            border.color: Theme.accentRed
            border.width: 1
        }

        Text {
            id: toastText
            anchors.centerIn: parent
            padding: 10
            font.family: Theme.fontFamily
            font.pixelSize: Theme.baseSize
            color: Theme.textPrimary
        }

        // Таймер для автозакрытия через 3 секунды
        Timer {
            id: toastTimer
            interval: 3000
            repeat: false
            onTriggered: toastPopup.close()
        }

        // Анимация появления
        enter: Transition {
            NumberAnimation {
                property: "opacity"
                from: 0.0
                to: 1.0
                duration: 300
            }
        }
        exit: Transition {
            NumberAnimation {
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: 300
            }
        }
    }

    // --- Глобальные всплывающие окна ---


    /*
       Эти ID используются в карточках по всему приложению
       через прямой доступ к корневым объектам.
    */

    /*! Глобальное окно подробностей предмета */
    SubjectPopup {
        id: globalSubjectPopup
    }

    /*! Глобальное окно подробностей дедлайна */
    DeadlinePopup {
        id: globalDeadlinePopup
    }

    /*! Глобальное окно списка дедлайнов по конкретному предмету */
    SubjectDeadlinesPopup {
        id: globalSubjectDeadlinesPopup
    }
}
