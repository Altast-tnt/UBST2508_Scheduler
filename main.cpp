#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/core/appcore.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

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
