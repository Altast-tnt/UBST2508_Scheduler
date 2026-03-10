#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace Config
{
    // Настройки приложения
    constexpr const char* AppName = "MyUniversityApp";
    constexpr const char* OrgName = "Scheduler";

    // Сеть
    constexpr const char* GoogleScriptUrl = "https://script.google.com/macros/s/AKfycbwwO9mYGbUwU23IKdULjzhoP8p9aitswx0oofqHTzYClhhmgJFb5M3i3ZW6RP0cF8nu/exec";

    // Ключи QSettings
    inline QString filePathKey(const QString& subjectName, const QString& fileName)
    {
        return "file_path_" + subjectName + "_" + fileName;
    }

    inline QString deadlineStatusKey(const QString& dateStr, const QString& desc)
    {
        return "deadline_" + dateStr + "_" + desc;
    }
}

#endif // CONSTANTS_H
