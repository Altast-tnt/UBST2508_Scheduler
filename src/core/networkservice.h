#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QMap>
#include <QDate>
#include <QList>

#include "src/entities/subject.h"
#include "src/core/typedefs.h"

class NetworkService : public QObject
{
    Q_OBJECT
public:
    explicit NetworkService(QObject *parent = nullptr);

    void fetchGoogleSheetsData();

    void downloadFile(const QString& url, const QString& savePath, File* fileObj);

signals:
    void dataReady(QList<Subject*> subjects,
                   LessonsMap lessonsMap,
                   DeadlinesMap deadlinesMap);

    void fetchError(QString errorMessage);

    void fileDownloaded(File* fileObj, const QString& savePath);

    void fileDownloadError(const QString& errorMessage);

private:
    QNetworkAccessManager* m_networkManager;

    void parseJson(const QByteArray &data);

    QDate parseDate(const QString &dateStr);
    QTime parseTime(const QString &timeStr);

    QList<Subject*> parseSubjects(const QJsonArray& subjectsArray, const QJsonObject& allFilesMap);
    LessonsMap parseSchedule(const QJsonArray& scheduleArray, const QList<Subject*>& subjects);
    DeadlinesMap parseDeadlines(const QJsonArray& deadlinesArray, const QJsonObject& allFilesMap, const QList<Subject*>& subjects);
};

#endif // NETWORKSERVICE_H
