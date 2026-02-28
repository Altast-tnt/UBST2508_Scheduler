#include "deadline.h"


Deadline::Deadline(QObject *parent)
    : QObject{parent}
{}

Subject *Deadline::subject() const
{
    return m_subject;
}

void Deadline::setSubject(Subject *newSubject)
{
    if (m_subject == newSubject)
        return;
    m_subject = newSubject;
    emit subjectChanged();
}

Deadline::DeadlineType Deadline::type() const
{
    return m_type;
}

void Deadline::setType(DeadlineType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

QDateTime Deadline::dateTime() const
{
    return m_dateTime;
}

void Deadline::setDateTime(const QDateTime &newDateTime)
{
    if (m_dateTime == newDateTime)
        return;
    m_dateTime = newDateTime;
    emit dateTimeChanged();
}

QString Deadline::description() const
{
    return m_description;
}

void Deadline::setDescription(const QString &newDescription)
{
    if (m_description == newDescription)
        return;
    m_description = newDescription;
    emit descriptionChanged();
}

bool Deadline::isCompleted() const
{
    return m_isCompleted;
}

void Deadline::setIsCompleted(bool newIsCompleted)
{
    if (m_isCompleted == newIsCompleted)
        return;
    m_isCompleted = newIsCompleted;
    emit isCompletedChanged();
}

QString Deadline::typeName() const
{
    switch(m_type)
    {
    case Deadline::PR:
        return "Практическая работа";
    case Deadline::KR:
        return "Контрольная работа";
    case Deadline::PRESENTATION:
        return "Презентация";
    case Deadline::DOKLAD:
        return "Доклад";
    case Deadline::REFERAT:
        return "Реферат";
    case Deadline::LAB:
        return "Лабораторная работа";
    default:
        return "Задание";
    }
}

QList<File *> Deadline::files() const
{
    return m_files;
}

void Deadline::setFiles(const QList<File *> &newFiles)
{
    if (m_files == newFiles)
        return;
    m_files = newFiles;
    emit filesChanged();
}

void Deadline::addFile(File *file)
{
    if (!file) return;
    for (auto f : std::as_const(m_files))
    {
        if (f->path() == file->path())
        {
            return;
        }
    }
    m_files.append(file);
    emit filesChanged();
}
