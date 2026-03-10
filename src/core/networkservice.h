#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QNetworkAccessManager>
#include <QObject>

#include <src/entities/lesson.h>
#include <src/entities/subject.h>

class NetworkService : public QObject
{
    Q_OBJECT
public:
    explicit NetworkService(QObject *parent = nullptr);
    void fetchGoogleSheetsData();

signals:
    void dataReady(QList<Subject*> subjects,
                   QMap<QDate, QList<Lesson*>> lessonsMap,
                   QMap<QDate, QList<Deadline*>> deadlinesMap);
    void fetchError(QString errorMessage);

private:
    QNetworkAccessManager* m_manager;

    // Модульные методы парсинга
    QList<Subject*> parseSubjects(const QJsonArray& arr, const QJsonObject& filesMap);
    QMap<QDate, QList<Lesson*>> parseSchedule(const QJsonArray& arr, const QList<Subject*>& subjects);
    QMap<QDate, QList<Deadline*>> parseDeadlines(const QJsonArray& arr, const QList<Subject*>& subjects, const QJsonObject& filesMap);
};

#endif // NETWORKSERVICE_H
