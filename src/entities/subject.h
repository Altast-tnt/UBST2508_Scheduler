#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>
#include <QString>
#include <QList>
#include "commonTypes.h"

class Deadline;

class Subject : public QObject
{
    Q_OBJECT

public:
    enum SubjectType
    {
        EXAM,
        CREDIT,
        CREDITWITHGRADE,
        MAX_TYPES
    };
    Q_ENUM(SubjectType);

    Q_PROPERTY(SubjectType type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QString typeName READ typeName NOTIFY typeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QList<Teacher*> teachers READ teachers WRITE setTeachers NOTIFY teachersChanged FINAL)
    Q_PROPERTY(QList<File*> files READ files WRITE setFiles NOTIFY filesChanged FINAL)
    Q_PROPERTY(QList<Deadline*> deadlines READ deadlines WRITE setDeadlines NOTIFY deadlinesChanged FINAL)

    explicit Subject(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    QList<Teacher *> teachers() const;
    void setTeachers(const QList<Teacher *> &newTeachers);
    void addTeacher(Teacher *teacher);

    QList<File *> files() const;
    void setFiles(const QList<File *> &newFiles);
    void addFile(File *file);

    QList<Deadline *> deadlines() const;
    void setDeadlines(const QList<Deadline *> &newDeadlines);
    void addDeadline(Deadline *deadline);

    SubjectType type() const;
    void setType(const SubjectType newType);

    QString typeName() const;


signals:
    void nameChanged();
    void teachersChanged();
    void filesChanged();
    void deadlinesChanged();

    void typeChanged();

private:
    QString m_name;
    QList<Teacher *> m_teachers;
    QList<File *> m_files;
    QList<Deadline *> m_deadlines;
    SubjectType m_type;
};

#endif // SUBJECT_H
