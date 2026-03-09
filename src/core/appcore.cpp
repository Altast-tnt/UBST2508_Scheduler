#include "appcore.h"
#include "src/entities/day.h"
#include "src/entities/commonTypes.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

Appcore::Appcore(QObject *parent)
    : QObject{parent}
{
    m_dayListModel = new DayListModel(this);
    m_fileModel = new FileListModel(this);
    m_subjectDeadlinesModel = new DeadlineListModel(this);
    m_networkManager = new QNetworkAccessManager(this);
}

void Appcore::loadTestData()
{

    Subject* math = new Subject(this);
    math->setName("Высшая математика");
    m_subjects.append(math);

    Teacher* historyTeacher = new Teacher();
    historyTeacher->setName("Лаврова Ирина Анатольевна");
    historyTeacher->setEmail("iralavrova@mail.com");

    File* presHistory = new File("Лекция 1", "../../lect1.pptx", File::PPTX, this);

    Subject* history = new Subject(this);
    history->setName("История России");
    history->addTeacher(historyTeacher);
    history->addFile(presHistory);
    m_subjects.append(history);

    Subject* prog = new Subject(this);
    prog->setName("Программирование");
    m_subjects.append(prog);


    QDate startDate = QDate::currentDate();

    for (int i = 0; i < 14; ++i) {
        QDate currentDate = startDate.addDays(i);
        Day* day = new Day(this);
        day->setDate(currentDate);


        ScheduleListModel* modelDay = new ScheduleListModel(day);
        DeadlineListModel* deadlineModelDay = new DeadlineListModel(day);
        QList<Lesson*> listDay;
        QList<Deadline*> deadlineListDay;


        if (currentDate.dayOfWeek() <= 5) {
            // Урок 1
            Lesson* l1 = new Lesson(day);
            l1->setSubject(math);
            l1->setType(Lesson::LECTION);
            l1->setStartTime(QTime(9, 0));
            l1->setEndTime(QTime(10, 30));
            listDay.append(l1);

            Lesson* l2 = new Lesson(day);
            l2->setSubject(history);
            l2->setType(Lesson::PRAKTIK);
            l2->setStartTime(QTime(10, 40));
            l2->setEndTime(QTime(12, 10));
            listDay.append(l2);

            Lesson* l3 = new Lesson(day);
            l3->setSubject(history);
            l3->setType(Lesson::PRAKTIK);
            l3->setStartTime(QTime(10, 40));
            l3->setEndTime(QTime(12, 10));
            listDay.append(l3);

            Lesson* l4 = new Lesson(day);
            l4->setSubject(history);
            l4->setType(Lesson::PRAKTIK);
            l4->setStartTime(QTime(10, 40));
            l4->setEndTime(QTime(12, 10));
            listDay.append(l4);

            Deadline* d1 = new Deadline(day);
            d1->setSubject(math);
            d1->setType(Deadline::PR);
            d1->setDateTime(QDateTime(currentDate, QTime(23, 59)));
            d1->setIsCompleted(false);
            math->addDeadline(d1);
            deadlineListDay.append(d1);


            File* labTask = new File("Задание на лабу", "../../lab1.pdf", File::PDF, this);

            Deadline* d2 = new Deadline(day);
            d2->setSubject(history);
            d2->setType(Deadline::KR);
            d2->setDateTime(QDateTime(currentDate, QTime(23, 59)));
            d2->setIsCompleted(true);
            d2->addFile(labTask);
            d2->setDescription(R"(Из прикрепленного файла взять по вариантам задание и подготовить реферат, правила оформления:
• 14 пт Times New Roman
• не менее 10 страниц А4
• наличие оглавления и титульного листа (не входят в количество страниц)
Прикрепить готовую работу в ЛМС)");
            history->addDeadline(d2);
            deadlineListDay.append(d2);

            File* labTask2 = new File("Задание на лабу222", "../../lab2.pdf", File::PDF, this);

            Deadline* d4 = new Deadline(day);
            d4->setSubject(history);
            d4->setType(Deadline::LAB);
            d4->setDateTime(QDateTime(currentDate, QTime(12, 59)));
            d4->setIsCompleted(false);
            d4->addFile(labTask2);
            d4->setDescription(R"(Из прикрепленного файла взять по вариантам задание и подготовить реферат, правила оформления:
Прикрепить готовую работу в ЛМС)");
            history->addDeadline(d4);
            deadlineListDay.append(d4);



            if (i % 2 == 0) {
                Lesson* l5 = new Lesson(day);
                l5->setSubject(history);
                l5->setType(Lesson::PRAKTIK);
                l5->setStartTime(QTime(10, 40));
                l5->setEndTime(QTime(12, 10));
                listDay.append(l5);

                Deadline* d3 = new Deadline(day);
                d3->setSubject(prog);
                d3->setType(Deadline::PR);
                d3->setDateTime(QDateTime(currentDate, QTime(23, 59)));
                d3->setIsCompleted(false);
                deadlineListDay.append(d3);

            } else {
                Lesson* l6 = new Lesson(day);
                l6->setSubject(prog);
                l6->setType(Lesson::LAB);
                l6->setStartTime(QTime(12, 30));
                l6->setEndTime(QTime(14, 0));
                listDay.append(l6);
            }
        }

        modelDay->setLessons(listDay);
        day->setDailyModel(modelDay);

        deadlineModelDay->setDeadlines(deadlineListDay);
        day->setDailyDeadlines(deadlineModelDay);

        m_dayListModel->addDay(day);



    }

    setCurrentSubject(math);
}

void Appcore::loadFromGoogleSheets()
{
    QNetworkRequest request(QUrl("https://script.google.com/macros/s/AKfycbwwO9mYGbUwU23IKdULjzhoP8p9aitswx0oofqHTzYClhhmgJFb5M3i3ZW6RP0cF8nu/exec"));
    QNetworkReply* reply = m_networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            parseAndApplyJson(response);
        }
        reply->deleteLater();
    });
}

Subject *Appcore::currentSubject() const
{
    return m_currentSubject;
}

void Appcore::setCurrentSubject(Subject *newCurrentSubject)
{
    if (m_currentSubject == newCurrentSubject)
        return;

    m_currentSubject = newCurrentSubject;

    if (m_currentSubject) {
        if (m_fileModel) {
            m_fileModel->setFiles(m_currentSubject->files());
        }

        if (m_subjectDeadlinesModel) {
            m_subjectDeadlinesModel->setDeadlines(m_currentSubject->deadlines());
        }
    } else {
        if (m_fileModel) m_fileModel->setFiles({});
        if (m_subjectDeadlinesModel) m_subjectDeadlinesModel->setDeadlines({});
    }

    emit currentSubjectChanged();
}

Deadline *Appcore::currentDeadline() const
{
    return m_currentDeadline;
}

void Appcore::setCurrentDeadline(Deadline *newCurrentDeadline)
{
    if (m_currentDeadline == newCurrentDeadline)
        return;
    m_currentDeadline = newCurrentDeadline;

    if (m_currentDeadline) {
        m_currentSubject = m_currentDeadline->subject();
        emit currentSubjectChanged();

        if (m_fileModel) {
            m_fileModel->setFiles(m_currentDeadline->files());
        }
    }
    emit currentDeadlineChanged();
}

QList<Subject *> Appcore::subjects() const
{
    return m_subjects;
}

void Appcore::setSubjects(const QList<Subject *> &newSubjects)
{
    if (m_subjects == newSubjects)
        return;
    m_subjects = newSubjects;
    emit subjectsChanged();
}

ScheduleListModel *Appcore::scheduleModel() const
{
    return m_scheduleModel;
}

void Appcore::setScheduleModel(ScheduleListModel *newScheduleModel)
{
    if (m_scheduleModel == newScheduleModel)
        return;
    m_scheduleModel = newScheduleModel;
    emit scheduleModelChanged();
}

DeadlineListModel *Appcore::deadlineModel() const
{
    return m_deadlineModel;
}

void Appcore::setDeadlineModel(DeadlineListModel *newDeadlineModel)
{
    if (m_deadlineModel == newDeadlineModel)
        return;
    m_deadlineModel = newDeadlineModel;
    emit deadlineModelChanged();
}

FileListModel *Appcore::fileModel() const
{
    return m_fileModel;
}

void Appcore::setFileModel(FileListModel *newFileModel)
{
    if (m_fileModel == newFileModel)
        return;
    m_fileModel = newFileModel;
    emit fileModelChanged();
}

DayListModel *Appcore::dayListModel() const
{
    return m_dayListModel;
}

void Appcore::setDayListModel(DayListModel *newDayListModel)
{
    if (m_dayListModel == newDayListModel)
        return;
    m_dayListModel = newDayListModel;
    emit dayListModelChanged();
}

DeadlineListModel *Appcore::subjectDeadlinesModel() const
{
     return m_subjectDeadlinesModel;
}

void Appcore::parseAndApplyJson(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Ошибка: JSON не является объектом!";
        return;
    }

    QJsonObject rootObj = doc.object();

    QJsonArray subjectsArray = rootObj["subjects"].toArray();
    QJsonArray scheduleArray = rootObj["schedule"].toArray();
    QJsonArray deadlinesArray = rootObj["deadlines"].toArray();


    for (const QJsonValue &value : std::as_const(subjectsArray))
    {

        QJsonArray row = value.toArray();

        // Получаем данные из JSON
        QString subjectName = row[0].toString();
        QString teacherName = row[1].toString();
        QString teacherEmail = row[2].toString();
        QString examTypeStr = row[3].toString();

        Subject::SubjectType sType = Subject::MAX_TYPES;
        examTypeStr = examTypeStr.trimmed().toUpper();

        if (examTypeStr == "EXAM")
        {
            sType = Subject::EXAM;
        } else if (examTypeStr == "CREDIT")
        {
            sType = Subject::CREDIT;
        } else if (examTypeStr == "CREDITWITHGRADE")
        {
            sType = Subject::CREDITWITHGRADE;
        }

        // Создаем учителя
        Teacher *teach = new Teacher(this);
        teach->setName(teacherName);
        teach->setEmail(teacherEmail);

        // Создаем предмет
        Subject *subj = new Subject(this);
        subj->addTeacher(teach);
        subj->setName(subjectName);
        subj->setType(sType);

        // Добавляем в общий список AppCore
        m_subjects.append(subj);
    }
    qDebug() << "Предметов загружено:" << m_subjects.count();

    QMap<QDate, QList<Lesson*>> daysMap;

    for (const QJsonValue &value : std::as_const(scheduleArray))
    {
        QJsonArray row = value.toArray();

        QString dateStr = row[0].toString();
        QString startTimeStr = row[1].toString();
        QString endTimeStr = row[2].toString();
        QString subjectName = row[3].toString();
        QString lessonTypeStr = row[4].toString();

        QDate lessonDate = QDate::fromString(dateStr, "dd.MM.yyyy");
        if (!lessonDate.isValid()) lessonDate = QDate::fromString(dateStr, "d.M.yyyy");
        if (!lessonDate.isValid()) lessonDate = QDate::fromString(dateStr, "d.M.yy"); // Для 22.4.26

        // Защита: если дата всё равно сломана, просто выкидываем этот урок!
        if (!lessonDate.isValid()) {
            qWarning() << "ПРОПУСК: Кривая дата в таблице:" << dateStr;
            continue;
        }

        // H - часы без обязательного нуля (9 или 09), m - минуты (30), s - секунды
        QTime startTime = QTime::fromString(startTimeStr, "H:m:s");
        if (!startTime.isValid()) startTime = QTime::fromString(startTimeStr, "H:m"); // Если секунд нет

        QTime endTime = QTime::fromString(endTimeStr, "H:m:s");
        if (!endTime.isValid()) endTime = QTime::fromString(endTimeStr, "H:m");

        // Защита: если время сломано, выводим в лог, но можем оставить (QML просто не покажет его)
        if (!startTime.isValid()) {
            qWarning() << "Кривое время старта:" << startTimeStr << "у предмета" << subjectName;
        }

        Subject *foundSubject = nullptr;
        for (Subject *s : std::as_const(m_subjects)) {
            if (s->name() == subjectName) {
                foundSubject = s;
                break;
            }
        }

        if (!foundSubject) {
            qWarning() << "Предмет не найден:" << subjectName;
            continue;
        }

        Lesson::LessonType lType = Lesson::MAX_TYPES;
        lessonTypeStr = lessonTypeStr.trimmed().toUpper();
        if (lessonTypeStr == "LECTION") lType = Lesson::LECTION;
        else if (lessonTypeStr == "PRAKTIK") lType = Lesson::PRAKTIK;
        else if (lessonTypeStr == "LAB") lType = Lesson::LAB;
        else if (lessonTypeStr == "KONTROL") lType = Lesson::KONTROL;
        else if (lessonTypeStr == "EXAM") lType = Lesson::EXAM;
        else if (lessonTypeStr == "RETAKE") lType = Lesson::RETAKE;

        Lesson *lesson = new Lesson(this);
        lesson->setSubject(foundSubject);
        lesson->setType(lType);
        lesson->setStartTime(startTime);
        lesson->setEndTime(endTime);
        lesson->setDate(lessonDate);

        daysMap[lessonDate].append(lesson);

    }

    for (auto it = daysMap.begin(); it != daysMap.end(); ++it) {

        // Создаем День
        Day* day = new Day(this);
        day->setDate(it.key());

        // Создаем Модель уроков для этого дня
        ScheduleListModel* modelDay = new ScheduleListModel(day);

        // Отдаем модели готовый список уроков из коробки
        modelDay->setLessons(it.value());

        // Прикрепляем модель к Дню
        day->setDailyModel(modelDay);

        // Добавляем готовый День в главную модель интерфейса!
        m_dayListModel->addDay(day);
    }

    if (!m_subjects.isEmpty()) {
        setCurrentSubject(m_subjects.first());
    }

    qDebug() << "Загрузка завершена! Дней создано:" << daysMap.keys().count();
}


