#include "appcore.h"
#include "src/entities/day.h"

Appcore::Appcore(QObject *parent)
    : QObject{parent}
{
    m_dayListModel = new DayListModel(this);
}

void Appcore::loadTestData()
{

    Subject* math = new Subject(this);
    math->setName("Высшая математика");
    m_subjects.append(math);

    Subject* history = new Subject(this);
    history->setName("История России");
    m_subjects.append(history);

    Subject* prog = new Subject(this);
    prog->setName("Программирование");
    m_subjects.append(prog);



    // ДЕНЬ 1
    Day* day1 = new Day(this);
    day1->setDate(QDate::currentDate());

    // Создаем внутреннюю модель уроков для этого дня
    ScheduleListModel* modelDay1 = new ScheduleListModel(day1);
    QList<Lesson*> listDay1;

    // Урок 1
    Lesson* l1 = new Lesson(day1);
    l1->setSubject(math);
    l1->setType(Lesson::LECTION);
    l1->setStartTime(QTime(9, 0));
    l1->setEndTime(QTime(10, 30));
    listDay1.append(l1);

    // Урок 2
    Lesson* l2 = new Lesson(day1);
    l2->setSubject(history);
    l2->setType(Lesson::LAB);
    l2->setStartTime(QTime(10, 40));
    l2->setEndTime(QTime(12, 10));
    listDay1.append(l2);

    // Загружаем список в модель дня и прикрепляем модель к дню
    modelDay1->setLessons(listDay1);
    day1->setDailyModel(modelDay1);

    // Добавляем день в главную модель
    m_dayListModel->addDay(day1);


    // ДЕНЬ 2
    Day* day2 = new Day(this);
    day2->setDate(QDate::currentDate().addDays(1));

    ScheduleListModel* modelDay2 = new ScheduleListModel(day2);
    QList<Lesson*> listDay2;

    // Урок 3
    Lesson* l3 = new Lesson(day2);
    l3->setSubject(prog);
    l3->setType(Lesson::LAB);
    l3->setStartTime(QTime(14, 0));
    l3->setEndTime(QTime(17, 0));
    listDay2.append(l3);

    modelDay2->setLessons(listDay2);
    day2->setDailyModel(modelDay2);

    m_dayListModel->addDay(day2);

    // --- НАСТРОЙКИ UI ---
    setCurrentSubject(math);
}

Subject *Appcore::currentSubject() const
{
    return m_currentSubject;
}

void Appcore::setCurrentSubject(Subject *newCurrentSubject)
{
    if (m_currentSubject == newCurrentSubject)
        return;
    m_currentSubject = newCurrentSubject;
    emit currentSubjectChanged();
}

Deadline *Appcore::currentDeadline() const
{
    return m_currentDeadline;
}

void Appcore::setCurrentDeadline(Deadline *newCurrentDeadline)
{
    if (m_currentDeadline == newCurrentDeadline)
        return;
    m_currentDeadline = newCurrentDeadline;
    emit currentDeadlineChanged();
}

QList<Subject *> Appcore::subjects() const
{
    return m_subjects;
}

void Appcore::setSubjects(const QList<Subject *> &newSubjects)
{
    if (m_subjects == newSubjects)
        return;
    m_subjects = newSubjects;
    emit subjectsChanged();
}

ScheduleListModel *Appcore::scheduleModel() const
{
    return m_scheduleModel;
}

void Appcore::setScheduleModel(ScheduleListModel *newScheduleModel)
{
    if (m_scheduleModel == newScheduleModel)
        return;
    m_scheduleModel = newScheduleModel;
    emit scheduleModelChanged();
}

// DeadlineListModel *Appcore::deadlineModel() const
// {
//     return m_deadlineModel;
// }

// void Appcore::setDeadlineModel(DeadlineListModel *newDeadlineModel)
// {
//     if (m_deadlineModel == newDeadlineModel)
//         return;
//     m_deadlineModel = newDeadlineModel;
//     emit deadlineModelChanged();
// }

// FileListModel *Appcore::fileModel() const
// {
//     return m_fileModel;
// }

// void Appcore::setFileModel(FileListModel *newFileModel)
// {
//     if (m_fileModel == newFileModel)
//         return;
//     m_fileModel = newFileModel;
//     emit fileModelChanged();
// }

DayListModel *Appcore::dayListModel() const
{
    return m_dayListModel;
}

void Appcore::setDayListModel(DayListModel *newDayListModel)
{
    if (m_dayListModel == newDayListModel)
        return;
    m_dayListModel = newDayListModel;
    emit dayListModelChanged();
}
