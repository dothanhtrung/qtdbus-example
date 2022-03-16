
#include "child.h"

#include <QDebug>

Child::Child(int sleepTimeout) : _sleepTimeout(sleepTimeout) {
    connect(&_timer, &QTimer::timeout, this, &Child::sleep);
    _timer.setSingleShot(true);
    _sleepy();
}

void Child::wakeup() {
    _slept = false;
    message("I'm awake");
    _sleepy();
}

void Child::sleep() {
    _slept = true;
    message("Go to sleep");
}

void Child::say(const QString &word) {
    if (_slept) {
        message("I'm sleep. Go away.");
    } else {
        qDebug() << "CHILD: " << word;
        _timer.stop();
        _sleepy();
    }
}

void Child::_sleepy() {
    if (_sleepTimeout > 0)
        _timer.start(_sleepTimeout);
}