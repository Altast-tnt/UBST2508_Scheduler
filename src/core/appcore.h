#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QList>
#include <QNetworkAccessManager>

#include "src/entities/deadline.h"
#include "src/entities/subject.h"

#include "src/models/schedulelistmodel.h"
#include "src/models/daylistmodel.h"
#include "src/models/deadlinelistmodel.h"
#include "src/models/filelistmodel.h"

/**
 * @class Appcore
 * @brief Центральный контроллер
 * Класс для передачи загруженных данных в модели для отрисовки UI
 */
class Appcore : public QObject
{
    Q_OBJECT
    /**
     * @brief Текущий предмет с файлами и дедлайнами (при наличии)
     */
    Q_PROPERTY(Subject* currentSubject READ currentSubject WRITE setCurrentSubject NOTIFY currentSubjectChanged FINAL)
    /**
     * @brief Текущий дедлайн с файлами (при наличии),
     * передается автоматически в соответствующий предмет
     */
    Q_PROPERTY(Deadline* currentDeadline READ currentDeadline WRITE setCurrentDeadline NOTIFY currentDeadlineChanged FINAL)
    /**
     * @brief Список предметов
     */
    Q_PROPERTY(QList<Subject*> subjects READ subjects WRITE setSubjects NOTIFY subjectsChanged FINAL)

    /**
     * @brief Модели для передачи данных в UI
     */
    Q_PROPERTY(ScheduleListModel* scheduleModel READ scheduleModel WRITE setScheduleModel NOTIFY scheduleModelChanged FINAL)
    Q_PROPERTY(DayListModel* dayListModel READ dayListModel WRITE setDayListModel NOTIFY dayListModelChanged FINAL)
    Q_PROPERTY(DayListModel* deadlinesDayListModel READ deadlinesDayListModel WRITE setDeadlinesDayListModel NOTIFY deadlinesDayListModelChanged FINAL)
    Q_PROPERTY(DeadlineListModel* deadlineModel READ deadlineModel WRITE setDeadlineModel NOTIFY deadlineModelChanged FINAL)
    Q_PROPERTY(FileListModel* fileModel READ fileModel WRITE setFileModel NOTIFY fileModelChanged FINAL)
    Q_PROPERTY(DeadlineListModel* subjectDeadlinesModel READ subjectDeadlinesModel CONSTANT)

public:
    /**
     * @brief Конструктор класса
     * инициализирует:
     * - m_dayListModel
     * - m_fileModel
     * - m_subjectDeadlinesModel
     * @param parent указатель на родительский объект QObject
     */
    explicit Appcore(QObject *parent = nullptr);

    /**
     * @brief Загружает тестовые данные,
     * заполняет:
     * - m_subjects
     * - m_dayListModel
     * передает данные моделям:
     * - ScheduleListModel
     * - DeadlineListModel
     */
    Q_INVOKABLE void loadTestData();

    Q_INVOKABLE void loadFromGoogleSheets();

    /**
     * @brief Возвращает текущий предмет, установленный в Appcore (m_currentSubject)
     * @return Subject*
     */
    Subject *currentSubject() const;
    /**
     * @brief Устанавливает текущий предмет
     * также синхронизирует модель файлов, дедлайнов с данными предмета
     * @param newCurrentSubject, указатель на объект предмета
     */
    void setCurrentSubject(Subject *newCurrentSubject);

    /**
     * @brief Возвращает текущий дедлайн, установленный в Appcore (m_currentDeadline)
     * @return Deadline*
     */
    Deadline *currentDeadline() const;
    /**
     * @brief Устанавливает текущий дедлайн
     * также синхронизирует модель файлов с данными дедлайна
     * и меняет m_currentSubject на свой собственный Subject
     * @param newCurrentDeadline, указатель на объект дедлайна
     */
    void setCurrentDeadline(Deadline *newCurrentDeadline);

    /**
     * @brief Возвращает список предметов, установленный в Appcore (m_subjects)
     * @return QList<Subject *>
     */
    QList<Subject *> subjects() const;
    /**
     * @brief Устанавливает новый список предметов в m_subjects
     * @param newSubjects, список указателей на предметы
     */
    void setSubjects(const QList<Subject *> &newSubjects);

    /**
     * @brief Возвращает модель предметов, установленную в Appcore (m_scheduleModel)
     * @return ScheduleListModel*, указатель на объект модели предметов
     */
    ScheduleListModel *scheduleModel() const;
    /**
     * @brief Устанавливает новую модель предметов в m_scheduleModel
     * @param newScheduleModel, указатель на объект модели предметов (ScheduleListModel)
     */
    void setScheduleModel(ScheduleListModel *newScheduleModel);

    /**
     * @brief Возвращает модель дедлайнов, установленную в Appcore (m_deadlineModel)
     * @return DeadlineListModel*, указатель на объект модели дедлайнов
     */
    DeadlineListModel *deadlineModel() const;
    /**
     * @brief Устанавливает новую модель дедлайнов в m_deadlineModel
     * @param newDeadlineModel, указатель на объект модели дедлайнов (DeadlineListModel)
     */
    void setDeadlineModel(DeadlineListModel *newDeadlineModel);

    /**
     * @brief Возвращает модель файлов, установленную в Appcore (m_fileModel)
     * @return FileListModel*, указатель на объект модели файлов
     */
    FileListModel *fileModel() const;
    /**
     * @brief Устанавливает новую модель файлов в m_fileModel
     * @param newFileModel, указатель на объект модели файлов (FileListModel)
     */
    void setFileModel(FileListModel *newFileModel);

    /**
     * @brief Возвращает модель дней, установленную в Appcore (m_dayListModel)
     * @return DayListModel*, указатель на объект модели дней
     */
    DayListModel *dayListModel() const;
    /**
     * @brief Устанавливает новую модель дней в m_dayListModel
     * @param newDayListModel, указатель на объект модели дней (DayListModel)
     */
    void setDayListModel(DayListModel *newDayListModel);

    /**
     * @brief Возвращает модель дедлайнов отфильтрованных по предмету,
     * установленную в Appcore (m_subjectDeadlinesModel)
     * @return DeadlineListModel*, указатель на объект модели дней
     */
    DeadlineListModel* subjectDeadlinesModel() const;

    DayListModel *deadlinesDayListModel() const;
    void setDeadlinesDayListModel(DayListModel *newDeadlinesDayListModel);

signals:
    void currentSubjectChanged();
    void currentDeadlineChanged();

    void subjectsChanged();

    void scheduleModelChanged();

    void deadlineModelChanged();

    void fileModelChanged();

    void dayListModelChanged();

    void deadlinesDayListModelChanged();

private:
    Subject *m_currentSubject = nullptr;
    Deadline *m_currentDeadline = nullptr;
    QList<Subject *> m_subjects;
    ScheduleListModel *m_scheduleModel = nullptr;
    DeadlineListModel *m_deadlineModel = nullptr;
    FileListModel *m_fileModel = nullptr;
    DayListModel *m_dayListModel = nullptr;
    DayListModel *m_deadlinesDayListModel = nullptr;
    DeadlineListModel *m_subjectDeadlinesModel = nullptr;
    QNetworkAccessManager *m_networkManager;

    void parseAndApplyJson(const QByteArray &data);

};

#endif // APPCORE_H
