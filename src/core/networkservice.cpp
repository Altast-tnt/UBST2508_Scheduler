#include "networkservice.h"
#include "src/core/constants.h"
#include "src/entities/commonTypes.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QSettings>

NetworkService::NetworkService(QObject *parent)
    : QObject{parent}
{
    m_networkManager = new QNetworkAccessManager(this);

}

void NetworkService::fetchGoogleSheetsData()
{
    QNetworkRequest request((QUrl(Config::GoogleScriptUrl)));
    QNetworkReply* reply = m_networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            parseJson(response);
        }
        reply->deleteLater();
    });
}

void NetworkService::parseJson(const QByteArray &data)
{
    QList<Subject*> parsedSubjects;
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Ошибка: JSON не является объектом!";
        return;
    }

    QJsonObject rootObj = doc.object();

    QSettings settings(Config::OrgName, Config::AppName);

    QJsonArray subjectsArray = rootObj["subjects"].toArray();
    QJsonArray scheduleArray = rootObj["schedule"].toArray();
    QJsonArray deadlinesArray = rootObj["deadlines"].toArray();

    QJsonObject allFilesMap = rootObj["driveFiles"].toObject();




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
        Teacher *teach = new Teacher();
        teach->setName(teacherName);
        teach->setEmail(teacherEmail);

        // Создаем предмет
        Subject *subj = new Subject();
        subj->addTeacher(teach);
        subj->setName(subjectName);
        subj->setType(sType);


        QJsonObject subjectFilesInfo = allFilesMap[subjectName].toObject();
        QJsonArray commonFiles = subjectFilesInfo["common"].toArray();

        for (const QJsonValue &fileVal : std::as_const(commonFiles)) {
            QJsonObject fileObj = fileVal.toObject(); // Превращаем значение в объект

            QString fileName = fileObj["name"].toString();
            QString fileUrl  = fileObj["url"].toString();
            QString typeStr  = fileObj["type"].toString().toUpper();

            // 1. Превращаем строку "PDF" в твой Enum FileType
            File::FileType fType = File::MAX_TYPES;
            if (typeStr == "PDF") fType = File::PDF;
            else if (typeStr == "XLSX" || typeStr == "XLS") fType = File::XLSX;
            else if (typeStr == "PPTX" || typeStr == "PPT") fType = File::PPTX;
            else if (typeStr == "DOCX" || typeStr == "DOC") fType = File::DOCX;

            // 2. Создаем объект файла
            // Путь (path) пока оставляем пустым, так как файл еще не на диске
            File *file = new File(fileName, fileUrl, "", fType, subjectName, subj);

            QString savedPath = settings.value(Config::filePathKey(file->subjectName(), file->name()), "").toString();

            if (!savedPath.isEmpty()) {
                // Проверяем, что файл всё еще реально существует на диске
                if (QFile::exists(savedPath)) {
                    file->setPath(savedPath);
                } else {
                    // Если пользователь удалил файл руками — чистим настройку
                    settings.remove(Config::filePathKey(file->subjectName(), file->name()));
                }
            }

            subj->addFile(file);
        }

        // Добавляем в общий список AppCore
        parsedSubjects.append(subj);
    }
    qDebug() << "Предметов загружено:" << parsedSubjects.count();

    QMap<QDate, QList<Lesson*>> lessonsMap;
    QMap<QDate, QList<Deadline*>> deadlinesMap;

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
        for (Subject *s : std::as_const(parsedSubjects)) {
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

        Lesson *lesson = new Lesson();
        lesson->setSubject(foundSubject);
        lesson->setType(lType);
        lesson->setStartTime(startTime);
        lesson->setEndTime(endTime);
        lesson->setDate(lessonDate);

        lessonsMap[lessonDate].append(lesson);

    }

    for (const QJsonValue &value : std::as_const(deadlinesArray)) {
        QJsonArray row = value.toArray();

        QString subjectName = row[0].toString();
        QString dateStr     = row[1].toString();
        QString timeStr     = row[2].toString();
        QString typeStr     = row[3].toString();
        QString descStr     = row[4].toString();


        QJsonObject subjectFilesInfo = allFilesMap[subjectName].toObject();

        QDate dDate = QDate::fromString(dateStr, "dd.MM.yyyy");
        if (!dDate.isValid()) dDate = QDate::fromString(dateStr, "d.M.yyyy");
        if (!dDate.isValid()) dDate = QDate::fromString(dateStr, "d.M.yy");
        if (!dDate.isValid()) continue;

        QTime dTime = QTime::fromString(timeStr, "H:m:s");
        if (!dTime.isValid()) dTime = QTime::fromString(timeStr, "H:m");


        Subject *foundSubject = nullptr;
        for (Subject *s : std::as_const(parsedSubjects)) {
            if (s->name() == subjectName) {
                foundSubject = s;
                break;
            }
        }
        if (!foundSubject) {
            qWarning() << "Предмет для дедлайна не найден:" << subjectName;
            continue;
        }


        Deadline::DeadlineType dType = Deadline::MAX_DEADLINETYPE;
        typeStr = typeStr.trimmed().toUpper();
        if (typeStr == "PR") dType = Deadline::PR;
        else if (typeStr == "KR") dType = Deadline::KR;
        else if (typeStr == "LAB") dType = Deadline::LAB;
        else if (typeStr == "PRESENTATION") dType = Deadline::PRESENTATION;
        else if (typeStr == "DOKLAD") dType = Deadline::DOKLAD;
        else if (typeStr == "REFERAT") dType = Deadline::REFERAT;

        Deadline* deadline = new Deadline();
        deadline->setSubject(foundSubject);
        deadline->setType(dType);
        deadline->setDateTime(QDateTime(dDate, dTime));
        deadline->setDescription(descStr);
        deadline->setIsCompleted(false);


        QString key = Config::deadlineStatusKey(deadline->dateTime().toString(), deadline->description());
        deadline->setIsCompleted(settings.value(key, false).toBool());


        QString folderKey = deadline->dateTime().toString("HH:mm dd.MM.yy");
        QJsonArray deadlineFiles = subjectFilesInfo["deadlines"].toObject()[folderKey].toArray();

        for (const QJsonValue &fileVal : std::as_const(deadlineFiles)) {
            QJsonObject fileObj = fileVal.toObject(); // Превращаем значение в объект

            QString fileName = fileObj["name"].toString();
            QString fileUrl  = fileObj["url"].toString();
            QString typeStr  = fileObj["type"].toString().toUpper();

            // 1. Превращаем строку "PDF" в твой Enum FileType
            File::FileType fType = File::MAX_TYPES;
            if (typeStr == "PDF") fType = File::PDF;
            else if (typeStr == "XLSX" || typeStr == "XLS") fType = File::XLSX;
            else if (typeStr == "PPTX" || typeStr == "PPT") fType = File::PPTX;
            else if (typeStr == "DOCX" || typeStr == "DOC") fType = File::DOCX;

            // 2. Создаем объект файла
            // Путь (path) пока оставляем пустым, так как файл еще не на диске
            File *file = new File(fileName, fileUrl, "", fType, subjectName, deadline);

            QString savedPath = settings.value(Config::filePathKey(file->subjectName(), file->name()), "").toString();

            if (!savedPath.isEmpty()) {
                // Проверяем, что файл всё еще реально существует на диске
                if (QFile::exists(savedPath)) {
                    file->setPath(savedPath);
                } else {
                    // Если пользователь удалил файл руками — чистим настройку
                    settings.remove(Config::filePathKey(file->subjectName(), file->name()));
                }
            }

            deadline->addFile(file);
        }


        foundSubject->addDeadline(deadline);
        deadlinesMap[dDate].append(deadline);
    }

    emit dataReady(parsedSubjects, lessonsMap, deadlinesMap);
}
