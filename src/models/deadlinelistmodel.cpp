#include "deadlinelistmodel.h"

DeadlineListModel::DeadlineListModel(QObject *parent)
{}

int DeadlineListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_deadlines.count();
}

QVariant DeadlineListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_deadlines.count())
    {
        return QVariant();
    }

    Deadline *deadline = m_deadlines.at(index.row());

    switch(role)
    {
    case SubjectNameRole:
        return (deadline->subject()) ? deadline->subject()->name() : QVariant();
    case DeadlineObjectRole:
        return QVariant::fromValue(deadline);
    case DeadlineTypesRole:
        return deadline->type();
    case DeadlineTypeNameRole:
        return deadline->typeName();
    case DeadlineDateTimeRole:
        return deadline->dateTime();
    case DeadlineIsCompletedRole:
        return deadline->isCompleted();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DeadlineListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SubjectNameRole] = "subjectName";
    roles[DeadlineObjectRole] = "deadlineObject";
    roles[DeadlineTypesRole] = "deadlineTypes";
    roles[DeadlineTypeNameRole] = "deadlineTypeName";
    roles[DeadlineDateTimeRole] = "deadlineDateTime";
    roles[DeadlineIsCompletedRole] = "deadlineIsCompleted";

    return roles;
}

void DeadlineListModel::setDeadlines(const QList<Deadline *> &deadlines)
{
    beginResetModel();
    m_deadlines = deadlines;
    endResetModel();
}
