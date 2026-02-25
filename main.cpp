#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/core/appcore.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<ScheduleListModel>("UBST2508_Sheduler", 1, 0, "ScheduleListModel", "Get from AppCore only");
    qmlRegisterUncreatableType<DayListModel>("UBST2508_Sheduler", 1, 0, "DayListModel", "Get from AppCore only");

    Appcore appcore;

    appcore.loadTestData();

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
