pragma Singleton

import QtQuick

QtObject {
    // Цветовая тема (светлая/темная)
    property bool isDark: false

    // Фон всего приложения
    readonly property color background: isDark ? "#111827" : "#F5F7FA"

    // Фон карточек
    readonly property color surface: isDark ? "#1F2937" : "#FFFFFF"

    // Основной текст
    readonly property color textPrimary: isDark ? "#F9FAFB" : "#1F2937"

    // Вторичный текст
    readonly property color textSecondary: isDark ? "#9CA3AF" : "#6B7280"

    // Акценты
    readonly property color accentRed: "#FB7185"
    readonly property color accentGreen: "#76FB71"
    readonly property color accentBlue: "#60A5FA"

    // Текст
    property string fontFamily: "sans-serif"
    property real baseSize: 16
    property real fontSizeSmall: baseSize * 0.8
    property real fontSizeLarge: baseSize * 1.5

    // Размерность элементов
    property real headerButtonSize: baseSize * 3
    property real columnWidthDayBoard: 250
    property real cardsWidth: 260
    property real fileCardHeight: 60
    property real checkBoxSize: 20
    property real fileIconSize: 40
    property real downloadBtnSize: 24
    property real segmentedToggleWidth: 340
    property real segmentedToggleWidthSmall: 230
    property real delegateDateRectHeight: 40
    property real dateRectHeight: 30

    // Скругленность элементов
    property real popupRadius: 30
    property real cardsRadius: 10
    property real segmentedToggleRadius: 40
    property real dateBubbleRadius: 20
}
