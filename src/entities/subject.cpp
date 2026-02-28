#include "subject.h"
#include "deadline.h"

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

// TODO: Подумать над возможностью и логичностью реализации через шаблоны
void Subject::addFile(File *file)
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

void Subject::addDeadline(Deadline *deadline)
{
    if (!deadline) return;

    for (auto existingDeadline : std::as_const(m_deadlines)) {

        if (existingDeadline->dateTime() == deadline->dateTime() &&
            existingDeadline->description() == deadline->description()) {
            return;
        }

    }

    deadline->setSubject(this);

    m_deadlines.append(deadline);
    emit deadlinesChanged();
}

Subject::SubjectType Subject::type() const
{
    return m_type;
}

void Subject::setType(const SubjectType newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

QString Subject::typeName() const
{
    switch(m_type)
    {
    case Subject::EXAM:
        return "Экзамен";
    case Subject::CREDIT:
        return "Зачет";
    case Subject::CREDITWITHGRADE:
        return "Зачет с оценкой";
    default:
        return "Итоговая работа";
    }
}

