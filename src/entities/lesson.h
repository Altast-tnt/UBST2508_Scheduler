#ifndef LESSON_H
#define LESSON_H

#include <QObject>
#include <QTime>
#include <QDate>
#include "subject.h"

class Lesson : public QObject
{
    Q_OBJECT
public:
    enum LessonType
    {
        LECTION,
        PRAKTIK,
        LAB,
        KONTROL,
        EXAM,
        RETAKE, // Пересдача
        MAX_TYPES
    };
    Q_ENUM(LessonType);

    Q_PROPERTY(LessonType type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(Subject* subject READ subject WRITE setSubject NOTIFY subjectChanged FINAL)
    Q_PROPERTY(QTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged FINAL)
    Q_PROPERTY(QTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged FINAL)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)


    explicit Lesson(QObject *parent = nullptr);

    LessonType type() const;
    void setType(LessonType newType);

    Subject *subject() const;
    void setSubject(Subject *newSubject);

    QTime startTime() const;
    void setStartTime(const QTime &newStartTime);

    QTime endTime() const;
    void setEndTime(const QTime &newEndTime);

    QDate date() const;
    void setDate(const QDate &newDate);

signals:
    void typeChanged();
    void subjectChanged();

    void startTimeChanged();

    void endTimeChanged();

    void dateChanged();

private:
    LessonType m_type = MAX_TYPES;
    Subject *m_subject = nullptr;
    QTime m_startTime;
    QTime m_endTime;
    QDate m_date;
};

#endif // LESSON_H
