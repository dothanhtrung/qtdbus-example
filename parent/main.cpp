#include "parent.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtDbus Example - Parent Process");
    parser.addHelpOption();
    QList<QCommandLineOption> optionList;
    optionList.append({{"c", "child-bin"}, "Path to child binary file", "child-bin",
                       QApplication::applicationDirPath() + "/../child/child"});
    parser.addOptions(optionList);
    parser.process(app);

    Parent *p = new Parent;
    p->setChildBinPath(parser.value("child-bin"));
    p->startChildProcess();
    p->resize(500, 500);
    p->show();

    QObject::connect(&app, &QApplication::aboutToQuit, p, &Parent::stopChildProcess);

    return app.exec();
}