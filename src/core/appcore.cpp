#include "appcore.h"

Appcore::Appcore(QObject *parent)
    : QObject{parent}
{}

void Appcore::loadTestData()
{
    Subject* math = new Subject(this);
    math->setName("Высшая математика");
    m_subjects.append(math);
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

// ScheduleListModel *Appcore::scheduleModel() const
// {
//     return m_scheduleModel;
// }

// void Appcore::setScheduleModel(ScheduleListModel *newScheduleModel)
// {
//     if (m_scheduleModel == newScheduleModel)
//         return;
//     m_scheduleModel = newScheduleModel;
//     emit scheduleModelChanged();
// }

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
