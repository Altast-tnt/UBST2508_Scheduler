#ifndef DEADLINE_H
#define DEADLINE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QDateTime>
#include "subject.h"

/**
 * @class Deadline
 * @brief Сущность дедлайна
 * Класс для хранения информации по дедлайну
 */
class Deadline : public QObject
{
    Q_OBJECT
 public:
    /**
    * @enum DeadlineType
    * @brief Перечисление возможных типов дедлайнов (заданий)
    */
    enum DeadlineType
    {
        PR,
        KR,
        PRESENTATION,
        DOKLAD,
        REFERAT,
        LAB,
        MAX_DEADLINETYPE
    };
    Q_ENUM(DeadlineType)

    /**
     * @brief Предмет, по которому установлен дедлайн
     */
    Q_PROPERTY(Subject* subject READ subject WRITE setSubject NOTIFY subjectChanged FINAL)
    /**
     * @brief Тип дедлайна из DeadlineType
     */
    Q_PROPERTY(DeadlineType type READ type WRITE setType NOTIFY typeChanged FINAL)
    /**
     * @brief Наименование типа дедлайна
     */
    Q_PROPERTY(QString typeName READ typeName NOTIFY typeChanged)
    /**
     * @brief Дата и время дедлайна
     */
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged FINAL)
    /**
     * @brief Описание дедлайна
     */
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)
    /**
     * @brief Значение, определяющее выполнен делайн пользователем или нет
     */
    Q_PROPERTY(bool isCompleted READ isCompleted WRITE setIsCompleted NOTIFY isCompletedChanged FINAL)
    /**
     * @brief Список файлов, относящихся к дедлайну
     */
    Q_PROPERTY(QList<File*> files READ files WRITE setFiles NOTIFY filesChanged FINAL)

    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit Deadline(QObject *parent = nullptr);

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
     * @brief Возвращает тип, установленный в m_type
     * @return DeadlineType
     */
    DeadlineType type() const;
    /**
     * @brief Возвращает тип дедлайна из строки typeStr (для парсинга)
     * @param typeStr, константная ссылка на строку с наименованием типа
     * @return DeadlineType
     */
    static DeadlineType strToType(const QString &typeStr);
    /**
     * @brief Устанавливает тип в m_type
     * @param newType, тип дедлайна (DeadlineType)
     */
    void setType(DeadlineType newType);

    /**
     * @brief Возвращает дату и время, установленные в m_dateTime
     * @return QDateTime
     */
    QDateTime dateTime() const;
    /**
     * @brief Устанавливает дату и время в m_dateTime
     * @param newDateTime, константная ссылка на объект даты и времени (QDateTime)
     */
    void setDateTime(const QDateTime &newDateTime);

    /**
     * @brief Возвращает описание дедлайна, установленное в m_description
     * @return QString
     */
    QString description() const;
    /**
     * @brief Устанавливает описание дедлайна в m_description
     * @param newDescription, константная ссылка на строку с описанием
     */
    void setDescription(const QString &newDescription);

    /**
     * @brief Возвращает значение выполненного дедлайна, установленное в m_isCompleted
     * @return bool
     */
    bool isCompleted() const;
    /**
     * @brief Устанавливает значение выполненного дедлайна в m_isCompleted
     * @param newIsCompleted, булево значение
     */
    void setIsCompleted(bool newIsCompleted);

    /**
     * @brief Возвращает название типа из DeadlineType
     * перевод enum->string
     * @return QString
     */
    QString typeName() const;

    /**
     * @brief Возвращает список файлов дедлайна, установленный в m_files
     * @return QList<File *>
     */
    QList<File *> files() const;
    /**
     * @brief Устанавливает список файлов дедлайна в m_files
     * @param newFiles, константная ссылка на список с файлами
     */
    void setFiles(const QList<File *> &newFiles);
    /**
     * @brief Добавляет файл в список файлов дедлайна - m_files,
     * проверяет валидность переданного параметра,
     * проводит поиск на дубликаты (по абсолютному пути файла)
     * @param file, указатель на объект файла
     */
    void addFile(File *file);

signals:
    void subjectChanged();
    void typeChanged();

    void dateTimeChanged();

    void descriptionChanged();

    void isCompletedChanged();

    void filesChanged();

private:
    Subject *m_subject = nullptr;
    DeadlineType m_type = MAX_DEADLINETYPE;
    QDateTime m_dateTime;
    QString m_description;
    bool m_isCompleted = false;
    QList<File *> m_files;
};

#endif // DEADLINE_H
