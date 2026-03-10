#include "testdatagenerator.h"

TestDataGenerator::TestDataGenerator(QObject *parent)
    : QObject{parent}
{}

void TestDataGenerator::generateMockData(QList<Subject *> &outSubjects, QMap<QDate, QList<Lesson *> > &outLessons, QMap<QDate, QList<Deadline *> > &outDeadlines)
{

    Subject* math = new Subject();
    math->setName("Высшая математика");
    outSubjects.append(math);

    Teacher* historyTeacher = new Teacher();
    historyTeacher->setName("Лаврова Ирина Анатольевна");
    historyTeacher->setEmail("iralavrova@mail.com");

    //File* presHistory = new File("Лекция 1", "", "../../lect1.pptx", File::PPTX, this);

    Subject* history = new Subject();
    history->setName("История России");
    history->addTeacher(historyTeacher);
    //history->addFile(presHistory);
    outSubjects.append(history);

    Subject* prog = new Subject();
    prog->setName("Программирование");
    outSubjects.append(prog);


    QDate startDate = QDate::currentDate();

    for (int i = 0; i < 14; ++i)
    {
        QDate currentDate = startDate.addDays(i);
        QList<Lesson*> listDay;
        QList<Deadline*> deadlineListDay;

        if (currentDate.dayOfWeek() <= 5)
        {
            // Создаем уроки и дедлайны
            Lesson* l1 = new Lesson();
            l1->setSubject(math);
            l1->setDate(currentDate);
            // ... настройки l1 ...
            listDay.append(l1);

            // ... остальные уроки ...

            Deadline* d1 = new Deadline();
            d1->setSubject(math);
            // ... настройки d1 ...
            math->addDeadline(d1);
            deadlineListDay.append(d1);
        }

        // КЛАДЕМ В СЛОВАРИ (вместо работы с DayListModel)
        if (!listDay.isEmpty()) outLessons[currentDate] = listDay;
        if (!deadlineListDay.isEmpty()) outDeadlines[currentDate] = deadlineListDay;
    }
}


