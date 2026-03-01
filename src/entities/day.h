#ifndef DAY_H
#define DAY_H

#include <QObject>
#include <QDate>
#include "src/models/schedulelistmodel.h"
#include "src/models/deadlinelistmodel.h"


/**
 * @class Day
 * @brief Сущность дня
 * Класс для хранения информации по дню
 */
class Day : public QObject
{
    Q_OBJECT
    /**
     * @brief Дата (стандартно - день, месяц, год)
     */
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)
    /**
     * @brief Модели для передачи данных в UI
     */
    Q_PROPERTY(ScheduleListModel* dailyModel READ dailyModel WRITE setDailyModel NOTIFY dailyModelChanged FINAL)
    Q_PROPERTY(DeadlineListModel* dailyDeadlines READ dailyDeadlines WRITE setDailyDeadlines NOTIFY dailyDeadlinesChanged FINAL)
public:
    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit Day(QObject *parent = nullptr);

    /**
     * @brief Возвращает дату, установленную в m_date
     * @return QDate
     */
    QDate date() const;
    /**
     * @brief Устанавливает дату
     * @param newDate, константная ссылка на объект даты (QDate)
     */
    void setDate(const QDate &newDate);

    /**
     * @brief Возвращает модель предметов, установленную в m_dailyModel
     * @return ScheduleListModel*, указатель на объект модели предметов
     */
    ScheduleListModel *dailyModel() const;
    /**
     * @brief Устанавливает новую модель предметов в m_dailyModel
     * @param newDailyModel, указатель на объект модели предметов (ScheduleListModel)
     */
    void setDailyModel(ScheduleListModel *newDailyModel);

    /**
     * @brief Возвращает модель дедлайнов, установленную в m_dailyDeadlines
     * @return DeadlineListModel*, указатель на объект модели дедлайнов
     */
    DeadlineListModel *dailyDeadlines() const;
    /**
     * @brief Устанавливает новую модель дедлайнов в m_dailyDeadlines
     * @param newDailyDeadlines, указатель на объект модели дедлайнов (DeadlineListModel)
     */
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
