#ifndef DAY_H
#define DAY_H

#include <QObject>
#include <QDate>
#include "src/models/schedulelistmodel.h"

class Day : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(ScheduleListModel* dailyModel READ dailyModel WRITE setDailyModel NOTIFY dailyModelChanged FINAL)
public:
    explicit Day(QObject *parent = nullptr);

    QDate date() const;
    void setDate(const QDate &newDate);

    ScheduleListModel *dailyModel() const;
    void setDailyModel(ScheduleListModel *newDailyModel);

signals:

    void dateChanged();
    void dailyModelChanged();

private:
    QDate m_date;
    ScheduleListModel *m_dailyModel = nullptr;
};

#endif // DAY_H
