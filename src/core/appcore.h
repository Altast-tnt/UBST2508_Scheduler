#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QList>
#include "src/entities/deadline.h"
#include "src/entities/subject.h"

#include "src/models/schedulelistmodel.h"
#include "src/models/daylistmodel.h"
// class DeadlineListModel;
// class FileListModel;

class Appcore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Subject* currentSubject READ currentSubject WRITE setCurrentSubject NOTIFY currentSubjectChanged FINAL)
    Q_PROPERTY(Deadline* currentDeadline READ currentDeadline WRITE setCurrentDeadline NOTIFY currentDeadlineChanged FINAL)
    Q_PROPERTY(QList<Subject*> subjects READ subjects WRITE setSubjects NOTIFY subjectsChanged FINAL)

    Q_PROPERTY(ScheduleListModel* scheduleModel READ scheduleModel WRITE setScheduleModel NOTIFY scheduleModelChanged FINAL)
    Q_PROPERTY(DayListModel* dayListModel READ dayListModel WRITE setDayListModel NOTIFY dayListModelChanged FINAL)
    // Q_PROPERTY(DeadlineListModel* deadlineModel READ deadlineModel WRITE setDeadlineModel NOTIFY deadlineModelChanged FINAL)
    // Q_PROPERTY(FileListModel* fileModel READ fileModel WRITE setFileModel NOTIFY fileModelChanged FINAL)

public:
    explicit Appcore(QObject *parent = nullptr);

    Q_INVOKABLE void loadTestData();

    Subject *currentSubject() const;
    void setCurrentSubject(Subject *newCurrentSubject);

    Deadline *currentDeadline() const;
    void setCurrentDeadline(Deadline *newCurrentDeadline);

    QList<Subject *> subjects() const;
    void setSubjects(const QList<Subject *> &newSubjects);

     ScheduleListModel *scheduleModel() const;
     void setScheduleModel(ScheduleListModel *newScheduleModel);

    // DeadlineListModel *deadlineModel() const;
    // void setDeadlineModel(DeadlineListModel *newDeadlineModel);

    // FileListModel *fileModel() const;
    // void setFileModel(FileListModel *newFileModel);

     DayListModel *dayListModel() const;
     void setDayListModel(DayListModel *newDayListModel);

 signals:
    void currentSubjectChanged();
    void currentDeadlineChanged();

    void subjectsChanged();

    void scheduleModelChanged();

    void deadlineModelChanged();

    void fileModelChanged();

    void dayListModelChanged();

private:
    Subject *m_currentSubject = nullptr;
    Deadline *m_currentDeadline = nullptr;
    QList<Subject *> m_subjects;
    ScheduleListModel *m_scheduleModel = nullptr;
    // DeadlineListModel *m_deadlineModel = nullptr;
    // FileListModel *m_fileModel = nullptr;
    DayListModel *m_dayListModel = nullptr;
};

#endif // APPCORE_H
