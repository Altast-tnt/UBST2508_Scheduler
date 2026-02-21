#include "lesson.h"


Lesson::Lesson(QObject *parent)
    : QObject{parent}
{}

Lesson::LessonType Lesson::type() const
{
    return m_type;
}

void Lesson::setType(LessonType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

Subject *Lesson::subject() const
{
    return m_subject;
}

void Lesson::setSubject(Subject *newSubject)
{
    if (m_subject == newSubject)
        return;
    m_subject = newSubject;
    emit subjectChanged();
}

QTime Lesson::startTime() const
{
    return m_startTime;
}

void Lesson::setStartTime(const QTime &newStartTime)
{
    if (m_startTime == newStartTime)
        return;
    m_startTime = newStartTime;
    emit startTimeChanged();
}

QTime Lesson::endTime() const
{
    return m_endTime;
}

void Lesson::setEndTime(const QTime &newEndTime)
{
    if (m_endTime == newEndTime)
        return;
    m_endTime = newEndTime;
    emit endTimeChanged();
}

QDate Lesson::date() const
{
    return m_date;
}

void Lesson::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}
