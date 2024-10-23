

#include "Client.h"

#include <QCoreApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString message = R"(<?xml version="1.0"?><UC_MESSAGE><VERSION VALUE="10"/><CONTENT CODE="0xE002" TIMESTAMP="2024-03-08 07:01:04.828" SERIAL_NO="serialA6E342" EVO_DEV_TYPE="1"/></UC_MESSAGE>\n)";
    QString certPath = "C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/certServer.pem";
    QString keyPath = "C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/gen2.advansys.si.key";

    QThread *thread = new QThread;
    ClientExample *clientExample = new ClientExample(message, certPath, keyPath);

    clientExample->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), clientExample, SLOT(send()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    //CLIENT NAJ LISTENA SAMO PO SENDU

    return a.exec();
}
