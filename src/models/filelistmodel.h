#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "src/entities/commonTypes.h"

/**
 * @class FileListModel
 * @brief Модель файла
 * Класс для передачи информации по файлам в UI
 */
class FileListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
    * @enum DeadlineRoles
    * @brief Перечисление ролей модели файла
    */
    enum FileRoles
    {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole,
        FileIconRole,
        FileObjectRole,
        FileIsDownloadingRole
    };

    /**
     * @brief Конструктор класса
     * @param parent указатель на родительский объект QObject
     */
    explicit FileListModel(QObject *parent = nullptr);

    /**
     * @brief Возвращает количество файлов, установленных в m_files
     * Для плоских списков возвращает 0, если передан валидный родитель
     * (так как у элементов списка нет дочерних элементов)
     * @param parent, родительский объект модели
     * @return int
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Возвращает данные, запрошенные по ролям модели, установленных в FileRoles
     * проверяет на валидность переданный индекс и текущее положение индекса в пределах m_files
     * @param index, индекс (координата) элемента в модели
     * @param role, роль из FileRoles
     * @return QVariant
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Возвращает хэш-сопоставление ролей и их названия, установленных в FileRoles
     * ключ - значение из FileRoles
     * значение - строка-наименование
     * Пример: roles[FileNameRole] = "fileName"
     * @return QHash<int, QByteArray>
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Обновляет список файлов в m_files,
     * Обновление происходит динамически
     * @param files, констанстная ссылка на список файлов
     */
    void setFiles(const QList<File*> &files);

private:
    QList<File*> m_files;

};

#endif // FILELISTMODEL_H
