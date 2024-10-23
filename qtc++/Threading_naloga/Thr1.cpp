
#include "Thr1.h"
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>

Thr1::Thr1(QObject* parent)
    : QObject(parent), timer_value_ms_(0), lowerBound_(0), upperBound_(0), timer(nullptr)
{}

Thr1::~Thr1()
{
    delete timer;
}

Thr1::Thr1(int timer_value_ms, int lowerBound, int upperBound, QObject* parent)
    : QObject(parent), timer_value_ms_(timer_value_ms), lowerBound_(lowerBound), upperBound_(upperBound), timer(nullptr)
{
    qDebug() << "Thr1 created with timer value: " << timer_value_ms << " and bounds: " << lowerBound << ", " << upperBound;
}

int Thr1::generateRandomNumber() const
{
    return QRandomGenerator::global()->bounded(lowerBound_, upperBound_);
}

void Thr1::startThread()
{
    // Create a QTimer instance ans start the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Thr1::onTimerTimeout);
    timer->start(timer_value_ms_);
}

void Thr1::onTimerTimeout()
{
    // Emit the signal with the random number
    int randomNumber = generateRandomNumber();
    qDebug() << QThread::currentThread()->objectName() << "Random Number:" << randomNumber;

    emit randomNumberGenerated(randomNumber);


}



