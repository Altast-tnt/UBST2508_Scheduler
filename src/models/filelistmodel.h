#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "src/entities/commonTypes.h"

class FileListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum FileRoles
    {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole,
        FileIconRole
    };

    explicit FileListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setFiles(const QList<File*> &files);

private:
    QList<File*> m_files;

};

#endif // FILELISTMODEL_H
