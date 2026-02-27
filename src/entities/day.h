#ifndef DAY_H
#define DAY_H

#include <QObject>
#include <QDate>
#include "src/models/schedulelistmodel.h"
#include "src/models/deadlinelistmodel.h"

class Day : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(ScheduleListModel* dailyModel READ dailyModel WRITE setDailyModel NOTIFY dailyModelChanged FINAL)
    Q_PROPERTY(DeadlineListModel* dailyDeadlines READ dailyDeadlines WRITE setDailyDeadlines NOTIFY dailyDeadlinesChanged FINAL)
public:
    explicit Day(QObject *parent = nullptr);

    QDate date() const;
    void setDate(const QDate &newDate);

    ScheduleListModel *dailyModel() const;
    void setDailyModel(ScheduleListModel *newDailyModel);

    DeadlineListModel *dailyDeadlines() const;
    void setDailyDeadlines(DeadlineListModel *newDailyDeadlines);

signals:

    void dateChanged();
    void dailyModelChanged();

    void dailyDeadlinesChanged();

private:
    QDate m_date;
    ScheduleListModel *m_dailyModel = nullptr;
    DeadlineListModel *m_dailyDeadlines = nullptr;
};

#endif // DAY_H
