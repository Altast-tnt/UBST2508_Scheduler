#include "appcore.h"
#include "src/entities/day.h"
#include "src/entities/commonTypes.h"

Appcore::Appcore(QObject *parent)
    : QObject{parent}
{
    m_dayListModel = new DayListModel(this);
    m_fileModel = new FileListModel(this);
}

void Appcore::loadTestData()
{

    Subject* math = new Subject(this);
    math->setName("Высшая математика");
    m_subjects.append(math);

    Teacher* historyTeacher = new Teacher();
    historyTeacher->setName("Лаврова Ирина Анатольевна");
    historyTeacher->setEmail("iralavrova@mail.com");

    File* presHistory = new File("Лекция 1", "../../lect1.pptx", File::PPTX, this);

    Subject* history = new Subject(this);
    history->setName("История России");
    history->addTeacher(historyTeacher);
    history->addFile(presHistory);
    m_subjects.append(history);

    Subject* prog = new Subject(this);
    prog->setName("Программирование");
    m_subjects.append(prog);


    QDate startDate = QDate::currentDate();

    for (int i = 0; i < 14; ++i) {
        QDate currentDate = startDate.addDays(i);
        Day* day = new Day(this);
        day->setDate(currentDate);


        ScheduleListModel* modelDay = new ScheduleListModel(day);
        DeadlineListModel* deadlineModelDay = new DeadlineListModel(day);
        QList<Lesson*> listDay;
        QList<Deadline*> deadlineListDay;


        if (currentDate.dayOfWeek() <= 5) {
            // Урок 1
            Lesson* l1 = new Lesson(day);
            l1->setSubject(math);
            l1->setType(Lesson::LECTION);
            l1->setStartTime(QTime(9, 0));
            l1->setEndTime(QTime(10, 30));
            listDay.append(l1);

            Lesson* l2 = new Lesson(day);
            l2->setSubject(history);
            l2->setType(Lesson::PRAKTIK);
            l2->setStartTime(QTime(10, 40));
            l2->setEndTime(QTime(12, 10));
            listDay.append(l2);

            Lesson* l3 = new Lesson(day);
            l3->setSubject(history);
            l3->setType(Lesson::PRAKTIK);
            l3->setStartTime(QTime(10, 40));
            l3->setEndTime(QTime(12, 10));
            listDay.append(l3);

            Lesson* l4 = new Lesson(day);
            l4->setSubject(history);
            l4->setType(Lesson::PRAKTIK);
            l4->setStartTime(QTime(10, 40));
            l4->setEndTime(QTime(12, 10));
            listDay.append(l4);

            Deadline* d1 = new Deadline(day);
            d1->setSubject(math);
            d1->setType(Deadline::PR);
            d1->setDateTime(QDateTime(currentDate, QTime(23, 59)));
            d1->setIsCompleted(false);
            deadlineListDay.append(d1);

            File* labTask = new File("Задание на лабу", "../../lab1.pdf", File::PDF, this);

            Deadline* d2 = new Deadline(day);
            d2->setSubject(history);
            d2->setType(Deadline::KR);
            d2->setDateTime(QDateTime(currentDate, QTime(23, 59)));
            d2->setIsCompleted(true);
            d2->addFile(labTask);
            d2->setDescription(R"(Из прикрепленного файла взять по вариантам задание и подготовить реферат, правила оформления:
• 14 пт Times New Roman
• не менее 10 страниц А4
• наличие оглавления и титульного листа (не входят в количество страниц)
Прикрепить готовую работу в ЛМС)");
            deadlineListDay.append(d2);



            if (i % 2 == 0) {
                Lesson* l5 = new Lesson(day);
                l5->setSubject(history);
                l5->setType(Lesson::PRAKTIK);
                l5->setStartTime(QTime(10, 40));
                l5->setEndTime(QTime(12, 10));
                listDay.append(l5);

                Deadline* d3 = new Deadline(day);
                d3->setSubject(prog);
                d3->setType(Deadline::PR);
                d3->setDateTime(QDateTime(currentDate, QTime(23, 59)));
                d3->setIsCompleted(false);
                deadlineListDay.append(d3);

            } else {
                Lesson* l6 = new Lesson(day);
                l6->setSubject(prog);
                l6->setType(Lesson::LAB);
                l6->setStartTime(QTime(12, 30));
                l6->setEndTime(QTime(14, 0));
                listDay.append(l6);
            }
        }

        modelDay->setLessons(listDay);
        day->setDailyModel(modelDay);

        deadlineModelDay->setDeadlines(deadlineListDay);
        day->setDailyDeadlines(deadlineModelDay);

        m_dayListModel->addDay(day);



    }

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

    if (m_currentSubject && m_fileModel) {
        m_fileModel->setFiles(m_currentSubject->files());
    }
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

    if (m_currentDeadline) {
        m_currentSubject = m_currentDeadline->subject();
        emit currentSubjectChanged();

        if (m_fileModel) {
            m_fileModel->setFiles(m_currentDeadline->files());
        }
    }
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

DeadlineListModel *Appcore::deadlineModel() const
{
    return m_deadlineModel;
}

void Appcore::setDeadlineModel(DeadlineListModel *newDeadlineModel)
{
    if (m_deadlineModel == newDeadlineModel)
        return;
    m_deadlineModel = newDeadlineModel;
    emit deadlineModelChanged();
}

FileListModel *Appcore::fileModel() const
{
    return m_fileModel;
}

void Appcore::setFileModel(FileListModel *newFileModel)
{
    if (m_fileModel == newFileModel)
        return;
    m_fileModel = newFileModel;
    emit fileModelChanged();
}

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
