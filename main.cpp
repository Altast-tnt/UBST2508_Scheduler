#include <QQmlContext>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "src/core/appcore.h"
#include "src/entities/commonTypes.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterUncreatableType<ScheduleListModel>("UBST2508_Sheduler", 1, 0, "ScheduleListModel", "Get from AppCore only");
    qmlRegisterUncreatableType<DayListModel>("UBST2508_Sheduler", 1, 0, "DayListModel", "Get from AppCore only");

    qmlRegisterUncreatableType<File>("UBST2508_Sheduler", 1, 0, "File", "Get from models only");

    qRegisterMetaType<File*>("File*");
    qRegisterMetaType<LessonsMap>("LessonsMap");
    qRegisterMetaType<DeadlinesMap>("DeadlinesMap");

    Appcore appcore;
    QQmlApplicationEngine engine;

    //appcore.loadTestData();
    appcore.loadFromGoogleSheets();

    engine.rootContext()->setContextProperty("appcore", &appcore);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("UBST2508_Sheduler", "Main");

    return app.exec();
}
