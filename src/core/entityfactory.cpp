#include "src/core/entityfactory.h"

#include <QJsonArray>
#include <QTime>

Subject* EntityFactory::createSubject(const QJsonArray& row)
{
    Subject* subj = new Subject();
    subj->setName(row[0].toString());
    subj->setType(Subject::strToType(row[3].toString()));

    Teacher* teach = new Teacher();
    teach->setName(row[1].toString());
    teach->setEmail(row[2].toString());
    subj->addTeacher(teach);
    return subj;
}

Lesson *EntityFactory::createLesson(const QJsonArray &row, Subject *subject, QDate date, QTime startTime, QTime endTime)
{
    Lesson* lesson = new Lesson();
    lesson->setSubject(subject);
    lesson->setStartTime(startTime);
    lesson->setEndTime(endTime);
    lesson->setType(Lesson::strToType(row[4].toString()));
    lesson->setDate(date);
    return lesson;
}

Deadline *EntityFactory::createDeadline(const QJsonArray &row, Subject *subject, QDateTime dateTime)
{
    Deadline* deadline = new Deadline();
    deadline->setSubject(subject);
    deadline->setType(Deadline::strToType(row[3].toString()));
    deadline->setDateTime(dateTime);
    deadline->setDescription(row[4].toString());
    deadline->setIsCompleted(false);

    return deadline;
}
