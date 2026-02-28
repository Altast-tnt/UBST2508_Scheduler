#ifndef DEADLINE_H
#define DEADLINE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QDateTime>
#include "subject.h"

class Deadline : public QObject
{
    Q_OBJECT
 public:
    enum DeadlineType
    {
        PR,
        KR,
        PRESENTATION,
        DOKLAD,
        REFERAT,
        LAB,
        MAX_DEADLINETYPE
        // TODO: Дополнить, если появятся еще типы работ

    };
    Q_ENUM(DeadlineType)

    Q_PROPERTY(Subject* subject READ subject WRITE setSubject NOTIFY subjectChanged FINAL)
    Q_PROPERTY(DeadlineType type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QString typeName READ typeName NOTIFY typeChanged)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged FINAL)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)
    Q_PROPERTY(bool isCompleted READ isCompleted WRITE setIsCompleted NOTIFY isCompletedChanged FINAL)
    Q_PROPERTY(QList<File*> files READ files WRITE setFiles NOTIFY filesChanged FINAL)

    explicit Deadline(QObject *parent = nullptr);

    Subject *subject() const;
    void setSubject(Subject *newSubject);

    DeadlineType type() const;
    void setType(DeadlineType newType);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    QString description() const;
    void setDescription(const QString &newDescription);

    bool isCompleted() const;
    void setIsCompleted(bool newIsCompleted);

    QString typeName() const;

    QList<File *> files() const;
    void setFiles(const QList<File *> &newFiles);
    void addFile(File *file);

signals:
    void subjectChanged();
    void typeChanged();

    void dateTimeChanged();

    void descriptionChanged();

    void isCompletedChanged();

    void filesChanged();

private:
    Subject *m_subject = nullptr;
    DeadlineType m_type = MAX_DEADLINETYPE;
    QDateTime m_dateTime;
    QString m_description;
    bool m_isCompleted = false;
    QList<File *> m_files;
};

#endif // DEADLINE_H
