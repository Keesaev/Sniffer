#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <sniffer.h>
#include <packetdata.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<Sniffer>("Sniffer", 1, 1, "Sniffer");
    qmlRegisterType<PacketData>("PacketData", 1, 1, "PacketData");
    engine.load(url);

    return app.exec();
}
