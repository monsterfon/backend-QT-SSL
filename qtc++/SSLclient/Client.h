


#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QSslSocket>

class ClientExample : public QObject
{
    Q_OBJECT

public:
    ClientExample(QObject* parent, const QString& CertificatePath, const QString& PrivateKeyPath, const QHostAddress& serverAddress, quint16 serverPort);


public slots:
    void send();

private:
    QString CertificatePath_;
    QString PrivateKeyPath_;
    QHostAddress serverAddress_;
    quint16 serverPort_;
    QSslSocket sslSocket;
    QString xmlContent_;
};

#endif //CLIENT_H
