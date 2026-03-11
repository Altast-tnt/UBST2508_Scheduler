#include "appcore.h"
#include "src/entities/day.h"
#include "src/entities/commonTypes.h"
#include "constants.h"

#include <QFile>
#include <QFileDialog>
#include <QSettings>

Appcore::Appcore(QObject *parent)
    : QObject{parent}
{
    m_dayListModel = new DayListModel(this);
    m_deadlinesDayListModel = new DayListModel(this);
    m_subjectFileModel = new FileListModel(this);
    m_deadlineFileModel = new FileListModel(this);
    m_subjectDeadlinesModel = new DeadlineListModel(this);

    m_netService = new NetworkService(this);
    connect(m_netService, &NetworkService::loadingStarted, this, [this](){setIsLoading(true);});

    connect(m_netService, &NetworkService::loadingFinished, this, [this](){setIsLoading(false);});
    connect(m_netService, &NetworkService::dataReady, this, &Appcore::onDataReady);
    connect(m_netService, &NetworkService::fileDownloaded, this, &Appcore::onFileDownloaded);
    connect(m_netService, &NetworkService::errorOccurred, this, &Appcore::showNotification);
    connect(m_netService, &NetworkService::fileDownloadFailed, this, &Appcore::onFileDownloadFailed);
}

void Appcore::initData()
{
    // Сначала грузим из файла
    m_netService->loadFromCache();

    // В фоне стучимся за новыми данными
    m_netService->fetchGoogleSheetsData();
}

void Appcore::refreshDataFromNetwork()
{
    // Пользователь нажал кнопку. Кэш не трогаем.
    emit showNotification("Обновление данных...");
    m_netService->fetchGoogleSheetsData();
}

void Appcore::clearCache()
{
    // Удаляем локальный JSON файл
    m_netService->clearLocalCache();

    // Сбрасываем все галочки и пути файлов в системном реестре
    QSettings settings(Config::OrgName, Config::AppName);
    settings.clear();

    // Очищаем интерфейс и оперативную память
    setCurrentSubject(nullptr);
    setCurrentDeadline(nullptr);

    m_dayListModel->clear();
    m_deadlinesDayListModel->clear();

    if (m_subjectFileModel) m_subjectFileModel->setFiles({});
    if (m_deadlineFileModel) m_deadlineFileModel->setFiles({});
    if (m_subjectDeadlinesModel) m_subjectDeadlinesModel->setDeadlines({});

    qDeleteAll(m_subjects);
    m_subjects.clear();

    // Сигнал, чтобы списки обновились (стали пустыми)
    emit subjectsChanged();

    // Показываем красивое уведомление (Toast)
    emit showNotification("Кэш и данные успешно очищены");
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
        if (m_subjectFileModel)
        {
            m_subjectFileModel->setFiles(m_currentSubject->files());
        }

        if (m_subjectDeadlinesModel)
        {
            m_subjectDeadlinesModel->setDeadlines(m_currentSubject->deadlines());
        }
    } else
    {
        if (m_subjectFileModel) m_subjectFileModel->setFiles({});
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

    if (m_currentDeadline)
    {
        m_currentSubject = m_currentDeadline->subject();
        emit currentSubjectChanged();

        if (m_deadlineFileModel)
        {
            m_deadlineFileModel->setFiles(m_currentDeadline->files());
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

FileListModel *Appcore::subjectFileModel() const
{
    return m_subjectFileModel;
}

void Appcore::setSubjectFileModel(FileListModel *newSubjectFileModel)
{
    if (m_subjectFileModel == newSubjectFileModel)
        return;
    m_subjectFileModel = newSubjectFileModel;
    emit subjectFileModelChanged();
}

FileListModel *Appcore::deadlineFileModel() const
{
    return m_deadlineFileModel;
}

void Appcore::setDeadlineFileModel(FileListModel *newDeadlineFileModel)
{
    if (m_deadlineFileModel == newDeadlineFileModel)
        return;
    m_deadlineFileModel = newDeadlineFileModel;
    emit deadlineFileModelChanged();
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

DayListModel *Appcore::deadlinesDayListModel() const
{
    return m_deadlinesDayListModel;
}

void Appcore::setDeadlinesDayListModel(DayListModel *newDeadlinesDayListModel)
{
    if (m_deadlinesDayListModel == newDeadlinesDayListModel)
        return;
    m_deadlinesDayListModel = newDeadlinesDayListModel;
    emit deadlinesDayListModelChanged();
}

void Appcore::saveDeadlineStatus(Deadline *deadline)
{
    QSettings settings(Config::OrgName, Config::AppName);
    QString key = Config::deadlineStatusKey(deadline->dateTime().toString(), deadline->description());
    settings.setValue(key, deadline->isCompleted());
}

void Appcore::downloadFile(File *file)
{
    if (!file) return;

    // Защита от повторного скачивания: если файл уже есть на диске, ничего не делаем
    if (!file->path().isEmpty() && QFile::exists(file->path()))
    {
        return;
    }

    // Спрашиваем путь у пользователя (UI)
    QString savePath = QFileDialog::getSaveFileName(nullptr, "Сохранить файл", file->name());
    if (savePath.isEmpty()) return; // Пользователь нажал "Отмена"

    // Индикатор загрузки
    file->setIsDownloading(true);

    // Даем команду (Сеть)
    m_netService->downloadFile(file->url(), savePath, file);
}

void Appcore::refreshSubjectFiles()
{
    if (m_currentSubject && m_subjectFileModel)
    {
        m_subjectFileModel->setFiles(m_currentSubject->files());
    }
}

void Appcore::onFileDownloaded(File *file, const QString &savePath)
{
    if (!file) return;

    // Загрузка завершена - отключаем индикатор
    file->setIsDownloading(false);

    // Обновляем объект
    file->setPath(savePath);

    // Сохраняем в кэш (чтобы помнить после перезагрузки)
    QSettings settings(Config::OrgName, Config::AppName);
    settings.setValue(Config::filePathKey(file->subjectName(), file->name()), savePath);

    // Синхронизируем дубликаты во всех предметах и дедлайнах!
    for (Subject* subj : std::as_const(m_subjects))
    {
        // Проверяем общие файлы предмета
        for (File* f : subj->files())
        {
            if (f->name() == file->name() && f->subjectName() == file->subjectName())
            {
                f->setPath(savePath);
            }
        }
        // Проверяем файлы дедлайнов
        for (Deadline* d : subj->deadlines())
        {
            for (File* f : d->files())
            {
                if (f->name() == file->name() && f->subjectName() == file->subjectName())
                {
                    f->setPath(savePath);
                }
            }
        }
    }
}

void Appcore::onFileDownloadFailed(File *file)
{
    if (file) {
        file->setIsDownloading(false);
    }
}


DeadlineListModel *Appcore::subjectDeadlinesModel() const
{
     return m_subjectDeadlinesModel;
}

void Appcore::onDataReady(QList<Subject *> subjects, QMap<QDate, QList<Lesson *> > lessonsMap, QMap<QDate, QList<Deadline *> > deadlinesMap)
{
    // Очистка UI и памяти
    setCurrentSubject(nullptr);
    setCurrentDeadline(nullptr);

    m_dayListModel->clear();
    m_deadlinesDayListModel->clear();

    qDeleteAll(m_subjects);
    m_subjects.clear();

    // Установка новых данных
    setSubjects(subjects);

    // Формирование UI-моделей
    QList<QDate> allDates = lessonsMap.keys();
    for (QDate d : deadlinesMap.keys())
    {
        if (!allDates.contains(d))
        {
            allDates.append(d);
        }
    }

    // Сортируем дни хронологически (от старых к новым)
    std::sort(allDates.begin(), allDates.end());

    // Создаем дни и модели
    for (QDate date : std::as_const(allDates))
    {
        Day* day = new Day(this);
        day->setDate(date);

        // Модель уроков (если в этот день нет уроков, value() вернет пустой список)
        ScheduleListModel* sModel = new ScheduleListModel(day);
        sModel->setLessons(lessonsMap.value(date));
        day->setDailyModel(sModel);

        // Модель дедлайнов
        DeadlineListModel* dModel = new DeadlineListModel(day);
        dModel->setDeadlines(deadlinesMap.value(date));
        day->setDailyDeadlines(dModel);

        m_dayListModel->addDay(day);
    }

    for (QDate date : deadlinesMap.keys())
    {
        Day* deadlineDay = new Day(this);
        deadlineDay->setDate(date);

        ScheduleListModel* sModel = new ScheduleListModel(deadlineDay);
        sModel->setLessons(lessonsMap.value(date));
        deadlineDay->setDailyModel(sModel);


        DeadlineListModel* dModel = new DeadlineListModel(deadlineDay);
        dModel->setDeadlines(deadlinesMap.value(date));
        deadlineDay->setDailyDeadlines(dModel);

        m_deadlinesDayListModel->addDay(deadlineDay);
    }
}

bool Appcore::isLoading() const
{
    return m_isLoading;
}

void Appcore::setIsLoading(bool loading)
{
    if (m_isLoading == loading) return;
    m_isLoading = loading;
    emit isLoadingChanged();
}
