pragma Singleton
import QtQuick

QtObject {
    property bool isDark: false

    // --- ЦВЕТОВАЯ ПАЛИТРА (На основе твоего дизайна) ---

    // Фон всего приложения
    readonly property color background: isDark ? "#111827" : "#F5F7FA"

    // Фон карточек (чуть светлее/темнее фона)
    readonly property color surface: isDark ? "#1F2937" : "#FFFFFF"

    // Основной текст
    readonly property color textPrimary: isDark ? "#F9FAFB" : "#1F2937"

    // Вторичный текст (время, преподаватель)
    readonly property color textSecondary: isDark ? "#9CA3AF" : "#6B7280"

    // Акценты
    readonly property color accentRed: "#FB7185"  // Для экзаменов/дедлайнов
    readonly property color accentGreen: "#76FB71" // Для практик
    readonly property color accentBlue: "#60A5FA"  // Для лекций

    // --- ШРИФТЫ ---
    // Если подключила Inter, можно добавить сюда настройки
    readonly property string mainFont: "sans-serif" // Или "Inter"
}
