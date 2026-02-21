#include "schedulelistmodel.h"

ScheduleListModel::ScheduleListModel(QObject* parent)
{}

int ScheduleListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_lessons.count();
}

QVariant ScheduleListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_lessons.count())
    {
        return QVariant();
    }

    Lesson *lesson = m_lessons.at(index.row());

    switch(role)
    {
    case SubjectNameRole:
        return (lesson->subject()) ? lesson->subject()->name() : QVariant();
    case LessonTypeRole:
        return lesson->type();
    case LessonStartTimeRole:
        return lesson->startTime();
    case LessonEndTimeRole:
        return lesson->endTime();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ScheduleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SubjectNameRole] = "subjectName";
    roles[LessonTypeRole] = "lessonType";
    roles[LessonStartTimeRole] = "lessonStartTime";
    roles[LessonEndTimeRole] = "lessonEndTime";
    roles[LessonDateRole] = "lessonDate";

    return roles;
}

void ScheduleListModel::setLessons(const QList<Lesson *> &lessons)
{
    beginResetModel();
    m_lessons = lessons;
    endResetModel();
}
