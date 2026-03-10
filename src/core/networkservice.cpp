#include "networkservice.h"
#include "src/core/constants.h"
#include "src/core/entityfactory.h"
#include "src/entities/commonTypes.h"

#include <QFile>
#include <QFileDialog>
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
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            parseJson(response);
        }
        reply->deleteLater();
    });
}

void NetworkService::downloadFile(const QString &url, const QString &savePath, File *fileObj)
{
    if (!fileObj || url.isEmpty() || savePath.isEmpty()) return;

    QNetworkRequest request((QUrl(url)));
    QNetworkReply* reply = m_networkManager->get(request);

    // Захватываем this (чтобы сделать emit), fileObj и savePath
    connect(reply, &QNetworkReply::finished, this,[this, fileObj, savePath, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();

            QFile f(savePath);
            if (f.open(QIODevice::WriteOnly))
            {
                f.write(response);
                f.close();


                emit fileDownloaded(fileObj, savePath);
            } else
            {
                emit fetchError("Не удалось открыть файл для записи");
            }
        } else
        {
            emit fetchError("Ошибка загрузки файла: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void NetworkService::parseJson(const QByteArray &data)
{


    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject())
    {
        qWarning() << "Ошибка: JSON не является объектом!";
        return;
    }
    QJsonObject rootObj = doc.object();

    auto subjects = parseSubjects(rootObj["subjects"].toArray(), rootObj["driveFiles"].toObject());
    auto lessons = parseSchedule(rootObj["schedule"].toArray(), subjects);
    auto deadlines = parseDeadlines(rootObj["deadlines"].toArray(), rootObj["driveFiles"].toObject(), subjects);

    qDebug() << "Предметов загружено:" << subjects.count();

    emit dataReady(subjects, lessons, deadlines);
}

QDate NetworkService::parseDate(const QString &dateStr)
{
    QDate d = QDate::fromString(dateStr, "dd.MM.yyyy");
    if (!d.isValid()) d = QDate::fromString(dateStr, "d.M.yyyy");
    if (!d.isValid()) d = QDate::fromString(dateStr, "d.M.yy");
    if (!d.isValid()) qWarning() << "ПРОПУСК: Кривая дата:" << dateStr;
    return d;
}

QTime NetworkService::parseTime(const QString &timeStr)
{
    QTime t = QTime::fromString(timeStr, "H:m:s");
    if (!t.isValid()) t = QTime::fromString(timeStr, "H:m");
    if (!t.isValid()) qWarning() << "Кривое время:" << timeStr;
    return t;
}

QList<Subject *> NetworkService::parseSubjects(const QJsonArray &subjectsArray, const QJsonObject &allFilesMap)
{
    QList<Subject*> parsedSubjects;
    QSettings settings(Config::OrgName, Config::AppName);

    for (const QJsonValue &value : std::as_const(subjectsArray))
    {
        Subject* subj = EntityFactory::createSubject(value.toArray());

        QJsonObject subjectFilesInfo = allFilesMap[subj->name()].toObject();
        QJsonArray commonFiles = subjectFilesInfo["common"].toArray();

        for (const QJsonValue &fileVal : std::as_const(commonFiles))
        {
            QJsonObject fileObj = fileVal.toObject();

            QString fileName = fileObj["name"].toString();
            QString fileUrl  = fileObj["url"].toString();
            QString typeStr  = fileObj["type"].toString().toUpper();

            // Превращаем строку в Enum FileType
            File::FileType fType = File::strToType(typeStr);

            // Создаем объект файла
            // Путь (path) пока оставляем пустым, так как файл еще не на диске
            File *file = new File(fileName, fileUrl, "", fType, subj->name(), subj);

            QString savedPath = settings.value(Config::filePathKey(file->subjectName(), file->name()), "").toString();

            if (!savedPath.isEmpty())
            {
                // Проверяем, что файл всё еще реально существует на диске
                if (QFile::exists(savedPath))
                {
                    file->setPath(savedPath);
                } else
                {
                    // Если пользователь удалил файл руками — чистим настройку
                    settings.remove(Config::filePathKey(file->subjectName(), file->name()));
                }
            }

            subj->addFile(file);
        }

        parsedSubjects.append(subj);
    }
    return parsedSubjects;
}

LessonsMap NetworkService::parseSchedule(const QJsonArray &scheduleArray, const QList<Subject *> &subjects)
{
    LessonsMap lessonsMap;

    for (const QJsonValue &value : std::as_const(scheduleArray))
    {
        QJsonArray row = value.toArray();
        QString subjectName = row[3].toString();

        // Ищем предмет
        Subject *foundSubject = nullptr;
        for (Subject *s : std::as_const(subjects))
        {
            if (s->name() == subjectName) { foundSubject = s; break; }
        }
        if (!foundSubject) continue;

        // 1. Парсим дату
        QDate lessonDate = parseDate(row[0].toString());
        if (!lessonDate.isValid()) continue; // Если дата кривая — пропускаем урок

        // Парсим время
        QTime startTime = parseTime(row[1].toString());
        QTime endTime = parseTime(row[2].toString());

        // Вызываем Фабрику
        Lesson* lesson = EntityFactory::createLesson(row, foundSubject, lessonDate, startTime, endTime);

        lessonsMap[lessonDate].append(lesson);
    }
    return lessonsMap;
}

DeadlinesMap NetworkService::parseDeadlines(const QJsonArray &deadlinesArray, const QJsonObject &allFilesMap, const QList<Subject *> &subjects)
{
    DeadlinesMap deadlinesMap;
    QSettings settings(Config::OrgName, Config::AppName);

    for (const QJsonValue &value : std::as_const(deadlinesArray))
    {
        QJsonArray row = value.toArray();
        QString subjectName = row[0].toString();

        // Ищем предмет
        Subject *foundSubject = nullptr;
        for (Subject *s : std::as_const(subjects))
        {
            if (s->name() == subjectName) { foundSubject = s; break; }
        }
        if (!foundSubject) continue;

        // Парсим дату и время
        QDate dDate = parseDate(row[1].toString());
        QTime dTime = parseTime(row[2].toString());
        if (!dDate.isValid()) continue;

        // Фабрика создает объект
        Deadline* deadline = EntityFactory::createDeadline(row, foundSubject, QDateTime(dDate, dTime));

        // Восстанавливаем галочку из QSettings
        QString key = Config::deadlineStatusKey(deadline->dateTime().toString(), deadline->description());
        deadline->setIsCompleted(settings.value(key, false).toBool());

        // Парсим файлы для этого дедлайна
        QString folderKey = deadline->dateTime().toString("HH:mm dd.MM.yy");
        QJsonObject subjectFilesInfo = allFilesMap[subjectName].toObject();
        QJsonArray deadlineFiles = subjectFilesInfo["deadlines"].toObject()[folderKey].toArray();

        for (const QJsonValue &fileVal : std::as_const(deadlineFiles))
        {
            QJsonObject fileObj = fileVal.toObject();
            File *file = new File(fileObj["name"].toString(), fileObj["url"].toString(), "",
                                  File::strToType(fileObj["type"].toString().toUpper()),
                                  subjectName, deadline);

            // Проверка кэша
            QString savedPath = settings.value(Config::filePathKey(subjectName, file->name()), "").toString();
            if (QFile::exists(savedPath)) file->setPath(savedPath);

            deadline->addFile(file);
        }

        foundSubject->addDeadline(deadline);
        deadlinesMap[dDate].append(deadline);
    }
    return deadlinesMap;
}
