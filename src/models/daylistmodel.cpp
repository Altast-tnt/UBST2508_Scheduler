#include "daylistmodel.h"

DayListModel::DayListModel(QObject *parent)
{}

int DayListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_days.count();
}

QVariant DayListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_days.count())
    {
        return QVariant();
    }
    Day *day = m_days.at(index.row());

    switch (role) {
    case DateStringRole:
        return day->date();
    case LessonsModelRole:
        return QVariant::fromValue(day->dailyModel());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DayListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DateStringRole] = "dateStringRole";
    roles[LessonsModelRole] = "lessonsModelRole";
    return roles;
}

void DayListModel::addDay(Day *day)
{
    if (!day) return;

    beginInsertRows(QModelIndex(), m_days.count(), m_days.count());

    m_days.append(day);

    endInsertRows();
}

