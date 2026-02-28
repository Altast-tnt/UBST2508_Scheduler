#include "filelistmodel.h"

FileListModel::FileListModel(QObject *parent)
{}

int FileListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_files.count();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_files.count())
    {
        return QVariant();
    }

    File *file = m_files.at(index.row());

    switch(role)
    {
    case FileNameRole:
        return file->name();
    case FilePathRole:
        return file->path();
    case FileIconRole:
        return file->icon();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FileListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileNameRole] = "fileName";
    roles[FilePathRole] = "filePath";
    roles[FileIconRole] = "fileIcon";
    return roles;
}

void FileListModel::setFiles(const QList<File *> &files)
{
    beginResetModel();
    m_files = files;
    endResetModel();
}
