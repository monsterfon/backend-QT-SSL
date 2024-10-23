#include <QCoreApplication>
#include <QRandomGenerator>
#include <QDebug>
#include <QtConcurrent>
#include <QFile>
#include <QTextStream>
#include <iostream>

#include "Thr1.h"
#include "Thr3.h"
#include "Thr4.h"

QPair<int, int> timerValues;


QPair<int, int> readTimerValues(const QString& filePath) {
    // Variables to store the timer values
    int thr1Timer_ms = 0;
    int thr2Timer_ms = 0;

    // Open the file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << file.errorString();
        return qMakePair(thr1Timer_ms, thr2Timer_ms);
    }

    // Read the file line by line
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        // Split the line by '=' to extract variable and value
        QStringList parts = line.split('=');

        if (parts.size() == 2) {
            QString variable = parts[0].trimmed();
            QString value = parts[1].trimmed();

            // Convert the value to an integer
            bool conversionOk;
            int intValue = value.toInt(&conversionOk);

            if (conversionOk) {
                // Assign the values to the corresponding variables
                if (variable == "thr1Timerm_ms") {
                    thr1Timer_ms = intValue;
                }
                else if (variable == "thr2Timerm_ms") {
                    thr2Timer_ms = intValue;
                }
            }
            else {
                qDebug() << "Failed to convert value to integer: " << value;
            }
        }
        else {
            qDebug() << "Invalid line format: " << line;
        }
    }

    // Close the file
    file.close();

    // Return the values using QPair
    return qMakePair(thr1Timer_ms, thr2Timer_ms);
}

QString getValidFilePath() {
    QString baseDir = QCoreApplication::applicationDirPath();

    while (true) {
        std::cout << "Enter the relative path to the main config.txt file: ";

        std::string relativePathStdString;
        std::getline(std::cin, relativePathStdString);

        QString relativePath = QString::fromStdString(relativePathStdString);
        relativePath = relativePath.trimmed();  // Trim leading and trailing whitespaces

        if (relativePath.compare("def", Qt::CaseInsensitive) == 0 || relativePath == "d") {
            qDebug() << "Using default path.";
            qDebug() << baseDir + "/config.txt";
            return baseDir + "/config.txt";  // Assuming config.txt is in the base directory
        }

        QString filePath = baseDir + "/" + relativePath;

        QFile file(filePath);

        // Check if the user has entered a valid path
        if (!file.exists()) {
            qDebug() << "Invalid path. Please enter a valid path.";
        }
        else {
            qDebug() << "Correct path.";
            return filePath;
        }
    }
}


int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    qInfo() <<"Avtor: Ziga Fon" ;





    // Get a valid file path from the user
    QString filePath = getValidFilePath();
    // Read timer values from the file
    QPair<int, int> timerValues = readTimerValues(filePath);
    qDebug() << "thr1Timer_ms: " << timerValues.first;
    qDebug() << "thr2Timer_ms: " << timerValues.second;

    if (timerValues.first < 10 || timerValues.first > 6000 ||
        timerValues.second < 10 || timerValues.second > 6000) {
        qDebug() << "Timer values are not in the valid range. Exiting...";
        return a.exec();
    }


    // Create Thread 1 that generates random number and emits them
    QThread* thread1 = new QThread(); //lower and upper bounds for rng
    Thr1* thr1 = new Thr1(timerValues.first, 1000000, 100000000);
    thr1->moveToThread(thread1); // Move thr1 to thread1
    thread1->setObjectName("Thread 1");
    QObject::connect(thread1, &QThread::started, thr1, &Thr1::startThread);
    QObject::connect(thread1, &QThread::finished, thread1, &QThread::deleteLater);


    // Create Thread 2 that generates random number and emits them
    QThread* thread2 = new QThread();//lower and upper bounds for rng
    Thr1* thr2 = new Thr1(timerValues.second, 1, 1000000);//
    thr2->moveToThread(thread2); // Move thr2 to thread2
    thread2->setObjectName("Thread 2");
    QObject::connect(thread2, &QThread::started, thr2, &Thr1::startThread);
    QObject::connect(thread2, &QThread::finished, thread2, &QThread::deleteLater);



    // Create Thread 3 that takes emitted values and calculates a diference and emits it
    QThread* thread3 = new QThread();
    Thr3* thr3 = new Thr3();
    thr3->moveToThread(thread3);
    thread3->setObjectName("Thread 3");
    QObject::connect(thread3, &QThread::started, thr3, &Thr3::startThread);
    QObject::connect(thread3, &QThread::finished, thread3, &QThread::deleteLater);




    // Connect the signal from Thr1 and thr2 to the slot in Thr3
    QObject::connect(thr1, &Thr1::randomNumberGenerated, thr3, &Thr3::queue1);
    QObject::connect(thr2, &Thr1::randomNumberGenerated, thr3, &Thr3::queue1);


    // Create Thread 4 that queues emitted values and writes them in a log.txt
    QThread* thread4 = new QThread();
    Thr4* thr4 = new Thr4();
    thr4->moveToThread(thread4);
    thread4->setObjectName("Thread 4");
    QObject::connect(thread4, &QThread::started, thr4, &Thr4::startThread);
    QObject::connect(thread4, &QThread::finished, thread4, &QThread::deleteLater);


    // Connect the signal to the slot
    QObject::connect(thr3, &Thr3::valuesAndDifference, thr4, &Thr4::handleValuesAndDifference);

    // Create a QTimer to stop the application after 5 minutes
    QTimer stopTimer;
    QObject::connect(&stopTimer, &QTimer::timeout, [&]() {
        qDebug() << "Program is exiting after 5 minutes.";
        thread1->quit();
        thread2->quit();
        thread3->quit();
        thread4->quit();
        a.quit();
        thr1 = nullptr;
        thr2 = nullptr;
        thr3 = nullptr;
        thr4 = nullptr;
        /*
        myQueue1.clear();
        myQueueValue1.clear();
        myQueueValue2.clear();
        myQueueDiference.clear();*/

        });
    stopTimer.setSingleShot(true);
    stopTimer.start(300000); // 5 minutes in milliseconds

    // Start all 4 threads
    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();



    return a.exec();
}
