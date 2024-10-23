//main.cpp


#include "ServerThread.h"

#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QList>
#include <QtCore/QCoreApplication>



int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);


    QString message = R"(<?xml version="1.0"?><UC_MESSAGE><VERSION VALUE="10"/><CONTENT CODE="0xE002" TIMESTAMP="2024-03-08 07:01:04.828" SERIAL_NO="serialA6E342" EVO_DEV_TYPE="1"/></UC_MESSAGE>\n)";
    QString certPath = "C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/certServer.pem";
    QString keyPath = "C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/gen2.advansys.si.key";

    // Create an instance of LoggerSSL
    LoggerSSL loggerSSL;
    QThread* thread = new QThread;
    ServerExample* serverExample = new ServerExample(nullptr, message, certPath, keyPath);


    serverExample->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), serverExample, SLOT(receive()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    QObject::connect(serverExample, &ServerExample::messageLogbook, &loggerSSL, &LoggerSSL::receiveLog );

    // always listening
    thread->start();


    // Sleep for a while (30 seconds) to simulate activity
    QThread::msleep(10000);

    // Stop the thread
    qDebug() << "Stopping thread...";
    QMetaObject::invokeMethod(serverExample, "stopThread", Qt::QueuedConnection);



    return a.exec();
}



