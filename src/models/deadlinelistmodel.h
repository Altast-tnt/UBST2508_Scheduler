#ifndef DEADLINELISTMODEL_H
#define DEADLINELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "src/entities/deadline.h"

/**
 * @class DeadlineListModel
 * @brief Модель дедлайна
 * Класс для передачи информации по дедлайнам в UI
 */
class DeadlineListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
    * @enum DeadlineRoles
    * @brief Перечисление ролей модели дедлайна
    */
    enum DeadlineRoles
    {
        SubjectNameRole = Qt::UserRole + 1,
        DeadlineObjectRole,
        DeadlineTypesRole,
        DeadlineTypeNameRole,
        DeadlineDateTimeRole,
        DeadlineIsCompletedRole,
        DeadlineDateOnlyRole
    };

    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit DeadlineListModel(QObject *parent = nullptr);

    /**
     * @brief Возвращает количество дедлайнов, установленных в m_deadlines
     * Для плоских списков возвращает 0, если передан валидный родитель
     * (так как у элементов списка нет дочерних элементов)
     * @param parent, родительский объект модели
     * @return int
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Возвращает данные, запрошенные по ролям модели, установленных в DeadlineRoles
     * проверяет на валидность переданный индекс и текущее положение индекса в пределах m_deadlines
     * @param index, индекс (координата) элемента в модели
     * @param role, роль из DeadlineRoles
     * @return QVariant
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Возвращает хэш-сопоставление ролей и их названия, установленных в DeadlineRoles
     * ключ - значение из DeadlineRoles
     * значение - строка-наименование
     * Пример: roles[DeadlineTypesRole] = "deadlineTypes"
     * @return QHash<int, QByteArray>
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Обновляет список дедлайнов в m_deadlines,
     * сортирует список m_deadlines по дате и времени дедлайна по возрастанию.
     * Обновление происходит динамически
     * @param deadlines, констанстная ссылка на список дедлайнов
     */
    void setDeadlines(const QList<Deadline*> &deadlines);

private:
    QList<Deadline*> m_deadlines;

};

#endif // DEADLINELISTMODEL_H
