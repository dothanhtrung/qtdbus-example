#include "child.h"
#include "child_adaptor.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtDbus Example - Child Process");
    parser.addHelpOption();
    QList<QCommandLineOption> optionList;
    optionList.append({{"s", "sleep-timeout"}, "Time to start sleep (msec)", "sleep-timeout", "5000"});
    parser.addOptions(optionList);
    parser.process(app);

    Child *c = new Child(parser.value("sleep-timeout").toInt());

    new ChildInterfaceAdaptor(c);
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/Child", c);
    connection.registerService("org.example.Child");

    return app.exec();
}