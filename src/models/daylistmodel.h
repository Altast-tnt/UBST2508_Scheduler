#ifndef DAYLISTMODEL_H
#define DAYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "src/entities/day.h"

/**
 * @class DayListModel
 * @brief Модель дня
 * Класс для передачи информации (уроков, дедлайнов) по дням в UI
 */
class DayListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
    * @enum DayRoles
    * @brief Перечисление ролей модели дня
    */
    enum DayRoles
    {
        DateStringRole = Qt::UserRole + 1,
        LessonsModelRole,
        DeadlinesModelRole
    };

    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit DayListModel(QObject *parent = nullptr);

    /**
     * @brief Возвращает количество дней, установленных в m_days
     * Для плоских списков возвращает 0, если передан валидный родитель
     * (так как у элементов списка нет дочерних элементов)
     * @param parent, родительский объект модели
     * @return int
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Возвращает данные, запрошенные по ролям модели, установленных в DayRoles
     * проверяет на валидность переданный индекс и текущее положение индекса в пределах m_days
     * @param index, индекс (координата) элемента в модели
     * @param role, роль из DayRoles
     * @return QVariant
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Возвращает хэш-сопоставление ролей и их названия, установленных в DayRoles
     * ключ - значение из DayRoles
     * значение - строка-наименование
     * Пример: roles[LessonsModelRole] = "lessonsModelRole"
     * @return QHash<int, QByteArray>
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Добавляет день в список m_days
     * проверяет на валидность переданный параметр
     * добавление дня происходит динамически
     * @param day, указатель на объект дня
     */
    void addDay(Day* day);

    /**
     * @brief Возвращает день из m_days (или nullptr, если день не найден) по переданной дате
     * @param date, константная ссылка на объект даты (QDate)
     * @return Day*
     */
    Q_INVOKABLE Day* getDay(const QDate &date) const;

private:
    QList<Day*> m_days;
};

#endif // DAYLISTMODEL_H
