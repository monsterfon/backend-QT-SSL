// Thr4.cpp

#include "Thr4.h"
#include <QTimer>
#include <QQueue>
#include <QThread>
#include <Qdebug>
#include <QFile>
QQueue<int> myQueueValue1;
QQueue<int> myQueueValue2;
QQueue<int> myQueueDiference;
//na queue sestavljen queuestring z informacijami o queue 1 do 3, pa regex za brat

Thr4::Thr4(QObject* parent) : QObject(parent)
{
    // Connect the signal to the slot

}

Thr4::~Thr4()
{}

void Thr4::handleValuesAndDifference(int value1, int value2, int difference)
{
    // enqueue all recieved values
    qDebug() << "Received values:" << value1 << value2;
    qDebug() << "Calculated difference:" << difference;
    qDebug() << "vrednosti so bile sprejete";

    myQueueValue1.enqueue(value1);
    myQueueValue2.enqueue(value2);
    myQueueDiference.enqueue(difference);


}


void Thr4::startThread() {
   // Create a QTimer instance
    timer = new QTimer(this);

    // Connect the timeout signal of the timer to a slot
    connect(timer, &QTimer::timeout, this, &Thr4::onTimerTimeout);

    // Set the interval for the timer (Timer_ms in milliseconds)
    timer->start(Timer_ms);
}

void Thr4::onTimerTimeout() {
    //Log 'thrd4' every 10 seconds in 'log.txt', also using QTimer
    qDebug() << "Updating log.txt";

    QFile outputFile("log.txt");
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QTextStream outStream(&outputFile);

        while (!myQueueValue1.isEmpty() && !myQueueValue2.isEmpty() && !myQueueDiference.isEmpty())
        {
            int value1 = myQueueValue1.dequeue();
            int value2 = myQueueValue2.dequeue();
            int difference = myQueueDiference.dequeue();

            // Write values to the file
            outStream << "Value1: " << value1 << ", Value2: " << value2 << ", Difference: " << difference << "\n";
        }

        // Close the file
        outputFile.close();
        qDebug() << "Values written to output.txt";
    }
    else
    {
        qDebug() << "Error opening the file!";
    }



}


