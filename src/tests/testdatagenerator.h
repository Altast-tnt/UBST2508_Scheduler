#ifndef TESTDATAGENERATOR_H
#define TESTDATAGENERATOR_H

#include <QList>
#include <QMap>
#include <QDate>
#include "src/entities/subject.h"
#include "src/entities/lesson.h"
#include "src/entities/deadline.h"

class TestDataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit TestDataGenerator(QObject *parent = nullptr);

    void generateMockData(QList<Subject*>& outSubjects,
                          QMap<QDate, QList<Lesson*>>& outLessons,
                          QMap<QDate, QList<Deadline*>>& outDeadlines);
};

#endif // TESTDATAGENERATOR_H
