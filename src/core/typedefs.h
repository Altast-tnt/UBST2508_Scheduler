#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <QMap>
#include <QDate>
#include <QList>

class Lesson;
class Deadline;

typedef QMap<QDate, QList<Lesson*>> LessonsMap;
typedef QMap<QDate, QList<Deadline*>> DeadlinesMap;

#endif // TYPEDEFS_H
