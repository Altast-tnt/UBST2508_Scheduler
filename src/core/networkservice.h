#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QMap>
#include <QDate>
#include <QList>

#include "src/entities/subject.h"
#include "src/entities/lesson.h"
#include "src/entities/deadline.h"
#include "src/core/typedefs.h"

class NetworkService : public QObject
{
    Q_OBJECT
public:
    explicit NetworkService(QObject *parent = nullptr);

    void fetchGoogleSheetsData();

signals:
    void dataReady(QList<Subject*> subjects,
                   LessonsMap lessonsMap,
                   DeadlinesMap deadlinesMap);

    void fetchError(QString errorMessage);

private:
    QNetworkAccessManager* m_networkManager;

    void parseJson(const QByteArray &data);
};

#endif // NETWORKSERVICE_H
