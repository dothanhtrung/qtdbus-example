
#include "parent.h"

#include <QToolButton>
#include <utility>

Parent::Parent(QWidget *parent) : QWidget(parent) {
    // Communicate with child process
    _childInterface = new org::example::Examples::ChildInterface("org.example.Child", "/Child",
                                                                 QDBusConnection::sessionBus(), this);
    connect(_childInterface, &org::example::Examples::ChildInterface::message, this, &Parent::messageFromChild);
    connect(this, &Parent::wakeup, _childInterface, &org::example::Examples::ChildInterface::wakeup);

    // Buttons
    _wakeupBtn = new QToolButton(this);
    _wakeupBtn->setText("WAKEUP");
    connect(_wakeupBtn, &QAbstractButton::clicked, this, &Parent::wakeup);
    _sayBtn = new QToolButton(this);
    _sayBtn->setText("SAY");
    connect(_sayBtn, &QAbstractButton::clicked, this, &Parent::makeChildTalk);

    // Layout
    _layout.addWidget(_wakeupBtn);
    _layout.addWidget(&_word);
    _layout.addWidget(_sayBtn);
    setLayout(&_layout);

    // Child process
    _childProcess.setProcessChannelMode(QProcess::ForwardedChannels);
    _childArgs << "-s 5000";
}

Parent::~Parent() {
    stopChildProcess();
}

void Parent::setChildBinPath(QString childBinPath) {
    _childBinPath = std::move(childBinPath);
}

void Parent::startChildProcess() {
    if (!_childBinPath.isEmpty())
        _childProcess.start(_childBinPath, _childArgs);
}

void Parent::messageFromChild(QString msg) {
    qDebug() << "PARENT: Message from child: " << msg;
}

void Parent::makeChildTalk() {
    // You also can call interface function directly
    _childInterface->say(_word.text());
}

void Parent::stopChildProcess() {
    _childProcess.terminate();
}