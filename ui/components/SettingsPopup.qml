import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

BasePopup {
    id: settingsPopup
    title: "Настройки"

    // Блок обновления
    ColumnLayout {
        Layout.fillWidth: true
        spacing: 5

        SettingsButton {
            id: btReloadData
            buttonText: "Обновить данные"

            onClicked: {
                appcore.refreshDataFromNetwork()
                settingsPopup.close()
            }
        }
        SettingsDescription {
            description: "Принудительно скачать свежее расписание и дедлайны из базы данных."
        }
    }

    // Блок очистки кэша
    ColumnLayout {
        Layout.fillWidth: true
        spacing: 5

        SettingsButton {
            buttonText: "Очистить кэш"
            onClicked: {
                appcore.clearCache()
                settingsPopup.close()
            }
        }
        SettingsDescription {
            description: "Удалит сохраненное расписание и сбросит статусы выполнения ВСЕХ дедлайнов."
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
