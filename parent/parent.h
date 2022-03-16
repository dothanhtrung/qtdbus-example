
#ifndef QTDBUS_EXAMPLE_PARENT_H
#define QTDBUS_EXAMPLE_PARENT_H

#include "child_interface.h"

#include <QAbstractButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>

class Parent : public QWidget {
Q_OBJECT
public:
    explicit Parent(QWidget *parent = nullptr);
    ~Parent() override;
    void setChildBinPath(QString childBinPath);
    void startChildProcess();

public slots:
    void messageFromChild(QString msg);
    void makeChildTalk();
    void stopChildProcess();

signals:
    void wakeup();

private:
    QAbstractButton *_wakeupBtn;
    QAbstractButton *_sayBtn;
    QLineEdit _word;
    QHBoxLayout _layout;
    QProcess _childProcess;
    QString _childBinPath;
    QStringList _childArgs;
    org::example::Examples::ChildInterface *_childInterface;
};


#endif //QTDBUS_EXAMPLE_PARENT_H
