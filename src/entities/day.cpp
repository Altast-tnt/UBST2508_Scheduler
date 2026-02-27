#include "day.h"

Day::Day(QObject *parent)
    : QObject{parent}
{

}

QDate Day::date() const
{
    return m_date;
}

void Day::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

ScheduleListModel *Day::dailyModel() const
{
    return m_dailyModel;
}

void Day::setDailyModel(ScheduleListModel *newDailyModel)
{
    if (m_dailyModel == newDailyModel)
        return;
    m_dailyModel = newDailyModel;
    emit dailyModelChanged();
}

DeadlineListModel *Day::dailyDeadlines() const
{
    return m_dailyDeadlines;
}

void Day::setDailyDeadlines(DeadlineListModel *newDailyDeadlines)
{
    if (m_dailyDeadlines == newDailyDeadlines)
        return;
    m_dailyDeadlines = newDailyDeadlines;
    emit dailyDeadlinesChanged();
}
