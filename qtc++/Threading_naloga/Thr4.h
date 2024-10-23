// Thr4.h
#pragma once

#include <QObject>
#include <QTimer>

class Thr4 : public QObject
{
    Q_OBJECT

public:
    Thr4(QObject* parent = nullptr);
    ~Thr4();
    void startThread();
public slots:

    void handleValuesAndDifference(int value1, int value2, int difference);
private slots:
    void onTimerTimeout();
signals:
    void valuesAndDifference(int value1, int value2, int difference);

private:
    int Timer_ms = 10000;
    QTimer* timer = nullptr;
};
