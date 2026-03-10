#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>
#include <QString>
#include <QList>
#include "commonTypes.h"

class Deadline;

/**
 * @class Lesson
 * @brief Сущность предмета
 * Класс для хранения информации по предмету
 */
class Subject : public QObject
{
    Q_OBJECT

public:
    /**
    * @enum SubjectType
    * @brief Перечисление возможных типов итоговой аттестации по предмету
    */
    enum SubjectType
    {
        EXAM,
        CREDIT, // зачет
        CREDITWITHGRADE, // зачет с оценкой
        MAX_TYPES
    };
    Q_ENUM(SubjectType);

    /**
     * @brief Тип аттестации предмета из SubjectType
     */
    Q_PROPERTY(SubjectType type READ type WRITE setType NOTIFY typeChanged FINAL)
    /**
     * @brief Наименование типа аттестации предмета
     */
    Q_PROPERTY(QString typeName READ typeName NOTIFY typeChanged)
    /**
     * @brief Наименование предмета
     */
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    /**
     * @brief Список преподавателей предмета
     */
    Q_PROPERTY(QList<Teacher*> teachers READ teachers WRITE setTeachers NOTIFY teachersChanged FINAL)
    /**
     * @brief Список файлов по предмету
     */
    Q_PROPERTY(QList<File*> files READ files WRITE setFiles NOTIFY filesChanged FINAL)
    /**
     * @brief Список дедлайнов по предмету
     */
    Q_PROPERTY(QList<Deadline*> deadlines READ deadlines WRITE setDeadlines NOTIFY deadlinesChanged FINAL)

    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit Subject(QObject *parent = nullptr);

    /**
     * @brief Возвращает наименование предмета, установленное в m_name
     * @return QString
     */
    QString name() const;
    /**
     * @brief Устанавливает наименование предмета в m_name
     * @param newName, константная ссылка на строку с наименованием
     */
    void setName(const QString &newName);

    /**
     * @brief Возвращает список преподавателей по предмету, установленный в m_teachers
     * @return QList<Teacher *>
     */
    QList<Teacher *> teachers() const;
    /**
     * @brief Устанавливает список преподавателей по предмету в m_teachers
     * @param newTeachers, константная ссылка на список преподавателей
     */
    void setTeachers(const QList<Teacher *> &newTeachers);
    /**
     * @brief Добавляет преподавателя в список m_teachers по предмету,
     * проверяет валидность переданного параметра,
     * проверяет дубликаты по почте преподавателя
     * @param teacher, указатель на объект преподавателя
     */
    void addTeacher(Teacher *teacher);

    /**
     * @brief Возвращает список файлов по предмету, установленный в m_files
     * @return QList<File *>
     */
    QList<File *> files() const;
    /**
     * @brief Устанавливает список файлов по предмету в m_files
     * @param newFiles, константная ссылка на список файлов
     */
    void setFiles(const QList<File *> &newFiles);
    /**
     * @brief Добавляет файл в список m_files по предмету,
     * проверяет валидность переданного параметра,
     * проверяет дубликаты по абсолютному пути файла
     * @param file, указатель на объект файла
     */
    void addFile(File *file);

    /**
     * @brief Возвращает список дедлайнов по предмету, установленный в m_deadlines
     * @return QList<Deadline *>
     */
    QList<Deadline *> deadlines() const;
    /**
     * @brief Устанавливает список дедлайнов по предмету в m_deadlines
     * @param newDeadlines, константная ссылка на список дедлайнов
     */
    void setDeadlines(const QList<Deadline *> &newDeadlines);
    /**
     * @brief Добавляет дедлайн в список m_deadlines по предмету,
     * проверяет валидность переданного параметра,
     * проверяет дубликаты по дате и времени дедлайна и описанию дедлайна
     * @param deadline, указатель на объект дедлайна
     */
    void addDeadline(Deadline *deadline);

    /**
     * @brief Возвращает тип, установленный в m_type
     * @return SubjectType
     */
    SubjectType type() const;
    /**
     * @brief Возвращает тип предмета из строки typeStr (для парсинга)
     * @param typeStr, константная ссылка на строку с наименованием типа
     * @return SubjectType
     */
    static SubjectType strToType(const QString &typeStr);
    /**
     * @brief Устанавливает тип в m_type
     * @param newType, тип урока (SubjectType)
     */
    void setType(const SubjectType newType);
    /**
     * @brief Возвращает название типа из SubjectType
     * перевод enum->string
     * @return QString
     */
    QString typeName() const;


signals:
    void nameChanged();
    void teachersChanged();
    void filesChanged();
    void deadlinesChanged();

    void typeChanged();

private:
    QString m_name;
    QList<Teacher *> m_teachers;
    QList<File *> m_files;
    QList<Deadline *> m_deadlines;
    SubjectType m_type;
};

#endif // SUBJECT_H
