#ifndef SCHEDULELISTMODEL_H
#define SCHEDULELISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "src/entities/lesson.h"


class ScheduleListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LessonRoles
    {
        SubjectNameRole = Qt::UserRole + 1,
        SubjectObjectRole,
        LessonTypeRole,
        LessonTypeNameRole,
        LessonStartTimeRole,
        LessonEndTimeRole,
        LessonDateRole
    };

    explicit ScheduleListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setLessons(const QList<Lesson*> &lessons);

private:
    QList<Lesson*> m_lessons;
};

Q_DECLARE_METATYPE(ScheduleListModel*)
#endif // SCHEDULELISTMODEL_H
