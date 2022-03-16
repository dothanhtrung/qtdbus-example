
#ifndef QTDBUS_EXAMPLE_CHILD_H
#define QTDBUS_EXAMPLE_CHILD_H

#include <QObject>
#include <QTimer>

class Child : public QObject {
Q_OBJECT
public:
    explicit Child(int sleepTimeout = 5000);

public slots:
    void sleep();
    void wakeup();
    void say(const QString &word);

signals:
    void message(QString msg);

private:
    bool _slept = false;
    int _sleepTimeout;
    QTimer _timer;

    void _sleepy();
};


#endif //QTDBUS_EXAMPLE_CHILD_H
