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

/**
 * @class NetworkService
 * @brief Работа с сетью
 * Класс для парсинга данных и передачи в appcore
 */
class NetworkService : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса
     * инициализирует:
     * - m_networkManager
     * @param parent указатель на родительский объект QObject
     */
    explicit NetworkService(QObject *parent = nullptr);

    /**
     * @brief Отправка запроса по скрипту из конфига - GoogleScriptUrl
     * получение ответа и вызов парсера
     */
    void fetchGoogleSheetsData();

    /**
     * @brief Отправка запроса на скачивание файла по url из File
     * @param url, константная ссылка на строку с путем к скачиванию файла
     * @param savePath, константная ссылка на строку с абсолютным путем файла
     * (который пользователь выбрал для скачивания)
     * @param fileObj, указатель на объект файла (File)
     */
    void downloadFile(const QString& url, const QString& savePath, File* fileObj);

    /**
     * @brief Загрузка данных из КЭШа
     * использует getCacheFilePath() для нахождения/создания папки КЭШа
     * Если есть json файл с данными - парсинг через parseJson
     */
    void loadFromCache();

    /**
     * @brief Очистка данных из КЭШа
     * использует getCacheFilePath() для нахождения папки КЭШа
     * если есть файл - удаляем
     */
    void clearLocalCache();

signals:
    void dataReady(QList<Subject*> subjects,
                   LessonsMap lessonsMap,
                   DeadlinesMap deadlinesMap);

    void fetchError(QString errorMessage);

    void fileDownloaded(File* fileObj, const QString& savePath);

    void fileDownloadError(const QString& errorMessage);

    void loadingStarted();

    void loadingFinished();

    void errorOccurred(QString message);

    void fileDownloadFailed(File* fileObj);


private:
    QNetworkAccessManager* m_networkManager;

    /**
     * @brief Парсинг JSON из ответа (data)
     * вызов мелких парсеров:
     * - parseSubjects
     * - parseSchedule
     * - parseDeadlines
     * @param data, константная ссылка на массив байтов
     */
    void parseJson(const QByteArray &data);

    /**
     * @brief Парсинг даты и проверка на валидность
     * @param dateStr, константная ссылка на строку с датой
     * @return QDate
     */
    QDate parseDate(const QString &dateStr);
    /**
     * @brief Парсинг времени и проверка на валидность
     * @param timeStr, константная ссылка на строку с временем
     * @return QTime
     */
    QTime parseTime(const QString &timeStr);

    /**
     * @brief Парсинг предметов и создание объектов через фабрику в EntityFactory
     * @param subjectsArray, константная ссылка на JSON массив предметов
     * @param allFilesMap, константная ссылка на JSON объект с деревом файлов
     * (для создания объектов файлов, принадлежащих предмету)
     * @return QList<Subject*>
     */
    QList<Subject*> parseSubjects(const QJsonArray& subjectsArray, const QJsonObject& allFilesMap);
    /**
     * @brief Парсинг расписания (уроков) и создание объектов через фабрику в EntityFactory
     * @param scheduleArray, константная ссылка на JSON массив расписания (уроков)
     * @param subjects, константная ссылка на спискок предметов
     * (для создания объектов уроков, принадлежащих предмету)
     * @return QMap<QDate, QList<Lesson*>> (LessonsMap)
     */
    LessonsMap parseSchedule(const QJsonArray& scheduleArray, const QList<Subject*>& subjects);
    /**
     * @brief Парсинг дедлайнов и создание объектов через фабрику в EntityFactory
     * @param deadlinesArray, константная ссылка на JSON массив дедлайнов
     * @param allFilesMap, константная ссылка на JSON объект дерева файлов, принадлежащих дедлайну
     * @param subjects, константная ссылка на спискок предметов
     * (для создания объектов дедлайнов, принадлежащих предмету)
     * @return QMap<QDate, QList<Deadline*>> (DeadlinesMap)
     */
    DeadlinesMap parseDeadlines(const QJsonArray& deadlinesArray, const QJsonObject& allFilesMap, const QList<Subject*>& subjects);

    /**
     * @brief Получение пути к папке с кэшированными данными
     * (весь JSON полученный ранее)
     * @return QString
     */
    QString getCacheFilePath() const;
};

#endif // NETWORKSERVICE_H
