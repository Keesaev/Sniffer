#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <snifferwrapper.h>
#include <packetmodel.h>
#include <packet.h>

#include <QMetaType>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    app.setOrganizationName("keesaev");
    app.setOrganizationDomain("Sniffer");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<SnifferWrapper>("SnifferWrapper", 1, 1, "SnifferWrapper");
    qmlRegisterType<PacketModel>("PacketModel", 1, 1, "PacketModel");
    qRegisterMetaType<Packet>();
    engine.load(url);

    return app.exec();
}
