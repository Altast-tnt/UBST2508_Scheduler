#ifndef DEADLINELISTMODEL_H
#define DEADLINELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

class DeadlineListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum DeadlineRoles
    {
        SubjectNameRole = Qt::UserRole + 1,
        DeadlineTypesRole,
        DeadlineDateTimeRole,
        DeadlineIsCompletedRole
    };

    explicit DeadlineListModel(QObject *parent = nullptr);

signals:
};

#endif // DEADLINELISTMODEL_H
