#ifndef SCHEDULELISTMODEL_H
#define SCHEDULELISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "src/entities/lesson.h"

/**
 * @class ScheduleListModel
 * @brief Модель урока
 * Класс для передачи информации по уроку в UI
 */
class ScheduleListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
    * @enum LessonRoles
    * @brief Перечисление ролей модели урока
    */
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

    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit ScheduleListModel(QObject* parent = nullptr);

    /**
     * @brief Возвращает количество уроков, установленных в m_lessons
     * Для плоских списков возвращает 0, если передан валидный родитель
     * (так как у элементов списка нет дочерних элементов)
     * @param parent, родительский объект модели
     * @return int
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Возвращает данные, запрошенные по ролям модели, установленных в LessonRoles
     * проверяет на валидность переданный индекс и текущее положение индекса в пределах m_lessons
     * @param index, индекс (координата) элемента в модели
     * @param role, роль из LessonRoles
     * @return QVariant
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Возвращает хэш-сопоставление ролей и их названия, установленных в LessonRoles
     * ключ - значение из LessonRoles
     * значение - строка-наименование
     * Пример: roles[LessonTypeRole] = "lessonType"
     * @return QHash<int, QByteArray>
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Обновляет список дедлайнов в m_lessons,
     * Обновление происходит динамически
     * @param lessons, констанстная ссылка на список уроков
     */
    void setLessons(const QList<Lesson*> &lessons);

private:
    QList<Lesson*> m_lessons;
};

Q_DECLARE_METATYPE(ScheduleListModel*)
#endif // SCHEDULELISTMODEL_H
