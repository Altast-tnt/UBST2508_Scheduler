#ifndef COMMONTYPES_H
#define COMMONTYPES_H
#include <QObject>
#include <QString>


class Teacher : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged FINAL)


public:
    QString name() const;
    void setName(const QString &newName);

    QString email() const;
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


class File : public QObject
{
    Q_OBJECT

public:

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

    File(QString name, QString path, FileType type, QObject *parent = nullptr)
        : QObject(parent), m_name(name), m_path(path), m_type(type)
    {}

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged FINAL)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged FINAL)
    Q_PROPERTY(FileType type READ type NOTIFY typeChanged FINAL)

    QString name() const;
    void setName(const QString &newName);

    QString icon() const;

    QString path() const;
    void setPath(const QString &newPath);

    FileType type() const;

private:
    QString m_name;
    QString m_path;
    FileType m_type = MAX_TYPES;

signals:
    void nameChanged();
    void iconChanged();
    void pathChanged();
    void typeChanged();
};

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
        return ":/assets/icons/docx.svg";
    case File::PDF:
        return ":/assets/icons/pdf.svg";
    case File::PPT:
    case File::PPTX:
        return ":/assets/icons/pptx.svg";
    case File::XLS:
    case File::XLSX:
        return ":/assets/icons/xls.svg";
    default:
        return ":/assets/icons/file.svg";
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
