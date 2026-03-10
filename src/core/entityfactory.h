#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <QJsonObject>
#include "src/entities/subject.h"
#include "src/entities/lesson.h"
#include "src/entities/deadline.h"

namespace EntityFactory
{
// Создаем предмет из JSON
Subject* createSubject(const QJsonArray& row);

// Создаем урок из JSON
Lesson* createLesson(const QJsonArray& row, Subject* subject, QDate date, QTime startTime, QTime endTime);

// Создаем дедлайн из JSON
Deadline* createDeadline(const QJsonArray& row, Subject* subject, QDateTime dateTime);
}

#endif // ENTITYFACTORY_H
