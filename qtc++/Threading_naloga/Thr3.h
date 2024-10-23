#pragma once

#include <QObject>
#include <QDebug>
#include <QTimer>

class Thr3 : public QObject
{
    Q_OBJECT

public:
    Thr3(QObject* parent = nullptr);
    ~Thr3();
    void startThread();

public slots:
    void queue1(int randomNumber);
    void onTimerTimeout();

private:
    int Timer_ms = 10;
    QTimer* timer = nullptr;  

signals:
    void valuesAndDifference(int value1, int value2, int difference);

};


