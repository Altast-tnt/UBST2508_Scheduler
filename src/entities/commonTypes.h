#ifndef COMMONTYPES_H
#define COMMONTYPES_H
#include <QObject>
#include <QString>

/**
 * @class Teacher
 * @brief Сущность преподавателя
 * Класс для хранения информации по преподавателю
 */
class Teacher : public QObject
{
    Q_OBJECT

    /**
     * @brief ФИО преподавателя
     */
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    /**
     * @brief Почта преподавателя
     */
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged FINAL)


public:
    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    Teacher(QObject *parent = nullptr)
        : QObject(parent)
    {}

    /**
     * @brief Возвращает ФИО преподавателя, установленное в m_name
     * @return QString
     */
    QString name() const;
    /**
     * @brief Устанавливает ФИО преподавателя в m_name
     * @param newName, константная ссылка на строку с ФИО
     */
    void setName(const QString &newName);

    /**
     * @brief Возвращает почту преподавателя, установленное в m_email
     * @return QString
     */
    QString email() const;
    /**
     * @brief Устанавливает почту преподавателя в m_email
     * @param newEmail, константная ссылка на строку с почтой
     */
    void setEmail(const QString &newEmail);

signals:
    void nameChanged();
    void emailChanged();

private:
    QString m_name;
    QString m_email;
};

inline QString Teacher::email() const
{
    return m_email;
}

inline void Teacher::setEmail(const QString &newEmail)
{
    if (m_email == newEmail)
        return;
    m_email = newEmail;
    emit emailChanged();
}

inline QString Teacher::name() const
{
    return m_name;
}

inline void Teacher::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

/**
 * @class File
 * @brief Сущность файла
 * Класс для хранения информации по файлу
 */
class File : public QObject
{
    Q_OBJECT

public:

    /**
    * @enum FileType
    * @brief Перечисление возможных типов файлов
    * На основе данного перечисления устанавливаются заранее подготовленные иконки
    */
    enum FileType
    {
        DOCX,
        DOC,
        XLS,
        XLSX,
        PDF,
        PPT,
        PPTX,
        MAX_TYPES
    };

    Q_ENUM(FileType)

    /**
     * @brief Конструктор класса
     * Инициализирует:
     * - m_name
     * - m_path
     * - m_type
     * @param name, наименование файла (без типа файла)
     * @param url, ссылка на скачивание файла
     * @param path, полный путь файла после скачивания
     * @param type, тип файла из перечисления FileType
     * @param parent, указатель на родительский объект QObject
     */
    File(QString name, QString url, QString path, FileType type, QObject *parent = nullptr)
        : QObject(parent), m_name(name), m_url(url), m_path(path), m_type(type)
    {}

    /**
     * @brief Наименование файла
     */
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)

    /**
     * @brief Ссылка на скачивание файла
     */
    Q_PROPERTY(QString url READ url NOTIFY urlChanged FINAL)

    /**
     * @brief Путь к иконке (определяется программно)
     */
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged FINAL)
    /**
     * @brief Абослютный путь к скачанному файлу
     */
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged FINAL)
    /**
     * @brief Тип файла (перечисление FileType)
     */
    Q_PROPERTY(FileType type READ type NOTIFY typeChanged FINAL)

    /**
     * @brief Возвращает наименование файла, установленное в m_name
     * @return QString
     */
    QString name() const;
    /**
     * @brief Устанавливает наименование файла в m_name
     * @param newName, константная ссылка на строку с наименованием файла
     */
    void setName(const QString &newName);

    /**
     * @brief Возвращает путь к иконке, установленный в m_icon
     * Иконка определяется на основе типа файла из FileType
     * @return QString
     */
    QString icon() const;

    /**
     * @brief Возвращает путь к скачанному файлу, установленный в m_path
     * @return QString
     */
    QString path() const;
    /**
     * @brief Устанавливает путь к скачанному файлу в m_path
     * @param newPath, константная ссылка на строку с путем к скачанному файлу
     */
    void setPath(const QString &newPath);

    /**
     * @brief Возвращает тип файла, установленный в m_type
     * @return FileType
     */
    FileType type() const;

    /**
     * @brief Возвращает ссылку на скачивание файла, установленный в m_url
     * @return QString
     */
    QString url() const;

    /**
     * @brief Устанавливает ссылку на скачивание файла в m_url
     * @param newUrl, константная ссылка на строку с ссылкой скачивания файла
     */
    void setUrl(const QString &newUrl);

    /**
     * @brief Возвращает название предмета, к которому относится файл, установленный в m_subjectName
     * @return QString
     */
    QString subjectName() const;

    /**
     * @brief Устанавливает название предмета, к которому относится файл в m_subjectName
     * @param newSubjectName, константная ссылка на строку с названием предмета
     */
    void setSubjectName(const QString &newSubjectName);


private:
    QString m_name;
    QString m_path = "";
    FileType m_type = MAX_TYPES;
    QString m_url = "";
    QString m_subjectName;

signals:
    void nameChanged();
    void iconChanged();
    void pathChanged();
    void typeChanged();
    void urlChanged();
    void subjectNameChanged();
};

inline QString File::url() const
{
    return m_url;
}

inline QString File::subjectName() const
{
    return m_subjectName;
}

inline void File::setSubjectName(const QString &newSubjectName)
{
    if (m_subjectName == newSubjectName)
        return;
    m_subjectName = newSubjectName;
    emit subjectNameChanged();
}

inline File::FileType File::type() const
{
    return m_type;
}

inline QString File::path() const
{
    return m_path;
}

inline void File::setPath(const QString &newPath)
{
    if (m_path == newPath)
        return;
    m_path = newPath;
    emit pathChanged();
}

inline QString File::icon() const
{
    switch (m_type) {
    case File::DOCX:
    case File::DOC:
        return "../../assets/icons/docx.svg";
    case File::PDF:
        return "../../assets/icons/pdf.svg";
    case File::PPT:
    case File::PPTX:
        return "../../assets/icons/pptx.svg";
    case File::XLS:
    case File::XLSX:
        return "../../assets/icons/xls.svg";
    default:
        return "../../assets/icons/file.svg";
    }
}

inline QString File::name() const
{
    return m_name;
}

inline void File::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

#endif // COMMONTYPES_H
