#include <QQmlContext>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include "src/core/appcore.h"
#include "src/entities/commonTypes.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("UBST2508 Scheduler");
    app.setOrganizationName("MyUniversityApp");
    app.setWindowIcon(QIcon(":/qt/qml/UBST2508_Sheduler/assets/icons/app_icon.png"));

    qmlRegisterUncreatableType<ScheduleListModel>("UBST2508_Sheduler", 1, 0, "ScheduleListModel", "Get from AppCore only");
    qmlRegisterUncreatableType<DayListModel>("UBST2508_Sheduler", 1, 0, "DayListModel", "Get from AppCore only");

    qmlRegisterUncreatableType<File>("UBST2508_Sheduler", 1, 0, "File", "Get from models only");

    qRegisterMetaType<File*>("File*");
    qRegisterMetaType<LessonsMap>("LessonsMap");
    qRegisterMetaType<DeadlinesMap>("DeadlinesMap");

    Appcore appcore;
    QQmlApplicationEngine engine;

    appcore.initData();

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
