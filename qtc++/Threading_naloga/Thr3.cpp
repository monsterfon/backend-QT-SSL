#include "Thr3.h"
#include <QTimer>
#include <QQueue>
#include <QThread>
#include <QtConcurrent>
#include <Qdebug>
QQueue<int> myQueue1;


Thr3::Thr3(QObject* parent) : QObject(parent) {}

Thr3::~Thr3() {}



void Thr3::queue1(int randomNumber) {

    // Do something with the received random number
    qDebug() << QThread:: currentThread()->objectName() << "recieved random number" << randomNumber << ": Queue size before add:" << myQueue1.size();
    myQueue1.enqueue(randomNumber);

    // Iterate through the elements using a const iterator
    for (auto it = myQueue1.constBegin(); it != myQueue1.constEnd(); ++it) {
        qDebug() << "queue" << *it;
    }


}




void Thr3::startThread() {
    // Create a QTimer instance
    timer = new QTimer(this);

    // Connect the timeout signal of the timer to a slot
    connect(timer, &QTimer::timeout, this, &Thr3::onTimerTimeout);

    // Set the interval for the timer (Timer_ms in milliseconds)
    timer->start(Timer_ms);
}

void Thr3::onTimerTimeout() {

    if (myQueue1.size() >= 2) {
        // Dequeue values from myQueue1 and myQueue2
        int value1 = myQueue1.dequeue();
        int value2 = myQueue1.dequeue();

        // Calculate the difference
        int difference = value1 - value2;

        // Emit the signal with the dequeued values and the difference
        qDebug() << "Values:" << value1 << "and" << value2 << ", Difference:" << difference;
        emit valuesAndDifference(value1, value2, difference);
    }


}


