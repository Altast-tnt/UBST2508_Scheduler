#include "subject.h"

Subject::Subject(QObject *parent)
    : QObject{parent}
{}

QString Subject::name() const
{
    return m_name;
}

void Subject::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QList<Teacher *> Subject::teachers() const
{
    return m_teachers;
}

void Subject::setTeachers(const QList<Teacher *> &newTeachers)
{
    if (m_teachers == newTeachers)
        return;
    m_teachers = newTeachers;
    emit teachersChanged();
}

void Subject::addTeacher(Teacher *teacher)
{
    if (!teacher) return;
    for (auto t : std::as_const(m_teachers))
    {
        if (t->email() == teacher->email())
        {
            return;
        }
    }
    m_teachers.append(teacher);
    emit teachersChanged();
}

QList<File *> Subject::files() const
{
    return m_files;
}

void Subject::setFiles(const QList<File *> &newFiles)
{
    if (m_files == newFiles)
        return;
    m_files = newFiles;
    emit filesChanged();
}

void Subject::addFile(File &file)
{

    for (auto f : std::as_const(m_files))
    {
        if (f->path() == file.path())
        {
            return;
        }
    }
    m_files.append(&file);
    emit filesChanged();
}

QList<Deadline *> Subject::deadlines() const
{
    return m_deadlines;
}

void Subject::setDeadlines(const QList<Deadline *> &newDeadlines)
{
    if (m_deadlines == newDeadlines)
        return;
    m_deadlines = newDeadlines;
    emit deadlinesChanged();
}
