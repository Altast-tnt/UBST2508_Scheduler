pragma Singleton

import QtQuick

QtObject {
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

    property string fontFamily: "sans-serif"
    property real baseSize: 16
    property real fontSizeSmall: baseSize * 0.8
    property real fontSizeLarge: baseSize * 1.5
}
