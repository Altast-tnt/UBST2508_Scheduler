#ifndef DEADLINELISTMODEL_H
#define DEADLINELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "src/entities/deadline.h"

class DeadlineListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum DeadlineRoles
    {
        SubjectNameRole = Qt::UserRole + 1,
        DeadlineTypesRole,
        DeadlineTypeNameRole,
        DeadlineDateTimeRole,
        DeadlineIsCompletedRole
    };

    explicit DeadlineListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setDeadlines(const QList<Deadline*> &deadlines);

private:
    QList<Deadline*> m_deadlines;

};

#endif // DEADLINELISTMODEL_H
