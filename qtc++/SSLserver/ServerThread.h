//ServerThread.h

#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H


#include <QObject>
#include <QHostAddress>
#include <QSslSocket>

// Global list declaration


class LoggerSSL : public QObject
{
    Q_OBJECT
public:
    QList<QString> logListSSL;

public slots:
    void receiveLog(const QString& errorMessage)
    {   // Add the error message to the global list
        logListSSL.append(errorMessage);
        // Log the error message
        qDebug() << "Entry added to the global log:" << errorMessage;
    }
};


class ServerExample : public QObject
{
    Q_OBJECT

public:
    ServerExample(QObject* parent = nullptr,
        QString xmlContent = "default_message",
        QString CertificatePath = "C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/certServer.pem",
        QString PrivateKeyPath_ = "C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/gen2.advansys.si.key",
        QHostAddress address_ = QHostAddress::LocalHost,
        quint16 port_ = 22333
        );
    //QSslSocket* sslSocket = nullptr,
    QString send(QString xmlContent = "default_message");


signals:

    void messageLogbook(const QString& error);

public slots:
    void receive();
    void stopThread();

private:

    // add host  adress    C:\Windows\System32\drivers\etc
    QHostAddress address_;
    quint16 port_ ;
    QString CertificatePath_ ;
    QString PrivateKeyPath_ ;
    //message to be sent
    QString xmlContent_ ;
    QSslSocket* sslSocket;
    bool running_;
};


#endif // SERVERTHREAD_H
