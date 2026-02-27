#ifndef DAYLISTMODEL_H
#define DAYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "src/entities/day.h"

class DayListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DayRoles
    {
        DateStringRole = Qt::UserRole + 1,
        LessonsModelRole,
        DeadlinesModelRole
    };
    explicit DayListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addDay(Day* day);

private:
    QList<Day*> m_days;
};

#endif // DAYLISTMODEL_H
