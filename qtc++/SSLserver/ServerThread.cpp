
//ServerThread.cpp
#include "ServerThread.h"
#include "SslServer.h"

#include <QCoreApplication>
#include <QHostAddress>
#include <QSslSocket>
#include <QThread>
#include <QTextStream>

ServerExample::ServerExample(QObject *parent ,QString xmlContent, QString CertificatePath, QString PrivateKeyPath, QHostAddress address , quint16 port) :
    QObject(parent), xmlContent_(xmlContent), CertificatePath_(CertificatePath), PrivateKeyPath_(PrivateKeyPath), address_(address), port_(port), sslSocket(nullptr), running_(true)
{

}



void ServerExample::receive()
{
    SslServer sslServer;
    sslServer.setSslLocalCertificate(CertificatePath_);
    sslServer.setSslPrivateKey(PrivateKeyPath_);
    sslServer.setSslProtocol(QSsl::TlsV1_3);
    QString errorOrMessage = "";

    if (!sslServer.listen(address_, port_))
    {
        emit messageLogbook(QString("ERROR: could not bind to %1:%2").arg(address_.toString()).arg(port_));
        return;
    }

    qDebug().nospace() << "Now listening on " << qPrintable(address_.toString()) << ":" << port_;


    while (running_) {
        if (!sslServer.waitForNewConnection(5000)) {
            emit messageLogbook(QString("ERROR: could not establish encrypted connection (%1)").arg(sslServer.errorString()));
            return;
        }

        sslSocket = dynamic_cast<QSslSocket*>(sslServer.nextPendingConnection());
        if (!sslSocket) {
            emit messageLogbook("ERROR: No valid SSL socket");
           // Try again for the next connection
        }

        qDebug() << "New connection";
        if (sslSocket->waitForReadyRead(1000)) {
            QByteArray message = sslSocket->readAll();
            qDebug() << "Message:" << QString(message);




            // Let the user provide their own receive-to-send function.



            errorOrMessage = send(message);

            emit messageLogbook(QString(errorOrMessage));
        }
        else {
            emit messageLogbook(QString("ERROR: could not receive message (%1)").arg(sslSocket->errorString()));
        }
    }








}


QString ServerExample::send(QString xmlContent)
{

    if (sslSocket)
    {
        sslSocket->write(xmlContent.toUtf8());

        if (sslSocket->waitForBytesWritten(30000))
        {
            qDebug() << "Message sent";
            return "Message sent";
        }
        else
        {
            return QString("ERROR: could not send message (%1)").arg(sslSocket->errorString());

        }
    }
    else
    {
        return "ERROR: sslSocket is null";
    }
}



void ServerExample::stopThread()
{
    qDebug() << "Thread stopping in progress";
    running_ = false;


    qDebug() << "Quitting current thread...";
    QThread::currentThread()->quit();
    //This wont be necesarry in final implementation
    qApp->exit();




    qDebug() << "Thread stopped!";
}