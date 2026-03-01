#ifndef LESSON_H
#define LESSON_H

#include <QObject>
#include <QTime>
#include <QDate>
#include "subject.h"

/**
 * @class Lesson
 * @brief Сущность урока
 * Класс для хранения информации по уроку
 */
class Lesson : public QObject
{
    Q_OBJECT
public:
    /**
    * @enum LessonType
    * @brief Перечисление возможных типов (видов) уроков
    */
    enum LessonType
    {
        LECTION,
        PRAKTIK,
        LAB,
        KONTROL,
        EXAM,
        RETAKE, // Пересдача
        MAX_TYPES
    };
    Q_ENUM(LessonType);

    /**
     * @brief Тип урока из LessonType
     */
    Q_PROPERTY(LessonType type READ type WRITE setType NOTIFY typeChanged FINAL)
    /**
     * @brief Наименование типа урока
     */
    Q_PROPERTY(QString typeName READ typeName NOTIFY typeChanged)
    /**
     * @brief Предмет, по которому установлен урок
     */
    Q_PROPERTY(Subject* subject READ subject WRITE setSubject NOTIFY subjectChanged FINAL)
    /**
     * @brief Время начала урока
     */
    Q_PROPERTY(QTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged FINAL)
    /**
     * @brief Время окончания урока
     */
    Q_PROPERTY(QTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged FINAL)
    /**
     * @brief Дата урока
     */
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged FINAL)

    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit Lesson(QObject *parent = nullptr);

    /**
     * @brief Возвращает тип, установленный в m_type
     * @return LessonType
     */
    LessonType type() const;
    /**
     * @brief Устанавливает тип в m_type
     * @param newType, тип урока (LessonType)
     */
    void setType(LessonType newType);

    /**
     * @brief Возвращает предмет, установленный в m_subject
     * @return Subject*
     */
    Subject *subject() const;
    /**
     * @brief Устанавливает предмет в m_subject
     * @param newSubject, указатель на объект предмета
     */
    void setSubject(Subject *newSubject);

    /**
     * @brief Возвращает время начала урока, установленное в m_startTime
     * @return QTime
     */
    QTime startTime() const;
    /**
     * @brief Устанавливает время начала урока в m_startTime
     * @param newStartTime, константная ссылка на объект времени (QTime)
     */
    void setStartTime(const QTime &newStartTime);

    /**
     * @brief Возвращает время конца урока, установленное в m_endTime
     * @return QTime
     */
    QTime endTime() const;
    /**
     * @brief Устанавливает время конца урока в m_endTime
     * @param newEndTime, константная ссылка на объект времени (QTime)
     */
    void setEndTime(const QTime &newEndTime);

    /**
     * @brief Возвращает дату урока, установленную в m_date
     * @return QDate
     */
    QDate date() const;
    /**
     * @brief Устанавливает дату урока в m_date
     * @param newDate, константная ссылка на объект даты (QDate)
     */
    void setDate(const QDate &newDate);

    /**
     * @brief Возвращает название типа из LessonType
     * перевод enum->string
     * @return QString
     */
    QString typeName() const;

signals:
    void typeChanged();
    void subjectChanged();

    void startTimeChanged();

    void endTimeChanged();

    void dateChanged();

private:
    LessonType m_type = MAX_TYPES;
    Subject *m_subject = nullptr;
    QTime m_startTime;
    QTime m_endTime;
    QDate m_date;
};

#endif // LESSON_H
