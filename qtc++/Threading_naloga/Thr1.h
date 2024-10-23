#pragma once

#include <QObject>
#include <QtConcurrent>
#include <QTimer>  // Include the necessary header for QTimer

class Thr1 : public QObject
{
    Q_OBJECT

public:
    Thr1(QObject* parent = nullptr);
    ~Thr1();
    explicit Thr1(int timer_value_ms, int lowerBound, int upperBound, QObject* parent = nullptr);

signals:
    void randomNumberGenerated(int randomNumber);

public slots:
    void startThread();

private slots:
    void onTimerTimeout();

private:
    int generateRandomNumber() const;
    //void startThread();


    int timer_value_ms_ = 0;
    int lowerBound_ = 0;
    int upperBound_ = 0;
    QTimer* timer = nullptr;
};
