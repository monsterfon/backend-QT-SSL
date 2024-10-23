#include "Client.h"

#include <QCoreApplication>
#include <QString>
#include <QSslSocket>
#include <QThread>
#include <QSslConfiguration>
#include <QSslKey>
#include <QFile>

ClientExample::ClientExample(QObject* parent, const QString& CertificatePath, const QString& PrivateKeyPath, const QHostAddress& serverAddress, quint16 serverPort)
    : QObject(parent),
    xmlContent_(xmlContent)
    CertificatePath_(CertificatePath),
    PrivateKeyPath_(PrivateKeyKeyPath),
    serverAddress_(serverAddress),
    serverPort_(serverPort),
    
{
}

void ClientExample::send()
{
    //message to be sent
    QString xmlContent = R"(<?xml version="1.0"?><UC_MESSAGE><VERSION VALUE="10"/><CONTENT CODE="0xE002" TIMESTAMP="2024-03-08 07:01:04.828" SERIAL_NO="serialA6E342" EVO_DEV_TYPE="1"/></UC_MESSAGE>\n)";
    QString hostName = "gen2.advansys.si";    // Matches the fully qualified domain name of the certificate
    quint16 port = 22333;
    QSslSocket sslSocket;


    //load the gen2.advansys.si.client.key
    QFile keyFile("C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/private.pem");
    if (!keyFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open private key file.";
        return;
    }
    QByteArray keyData = keyFile.readAll();
    keyFile.close();
    QSslKey sslKey(keyData, QSsl::Rsa, QSsl::Pem);
    if (sslKey.isNull()) qDebug() << "Failed to load SSL private key.";

    // Load CA certificates pem
    QList<QSslCertificate> caCertificates = QSslCertificate::fromPath("C:/Users/user/Desktop/sluzba2/projekti/internetna_varnost_ssl/gen2.certificate/certClient.pem");
    // Check if the list of certificates is empty, indicating that no certificates were loaded
    if (caCertificates.isEmpty()) {
        qDebug() << "No certificates found at the specified path.";
        // Handle the error or exit the function as needed
        return; // or use 'exit()' to exit the application
    }

    // Check if any of the loaded certificates are null, indicating that they are invalid
    bool hasInvalidCertificate = false;
    for (const QSslCertificate& certificate : caCertificates) {
        if (certificate.isNull()) {
            qDebug() << "One or more certificates in the file are invalid.";
            hasInvalidCertificate = true;
            // Handle the error or exit the function as needed
            break; // Exit the loop since we've found an invalid certificate
        }
    }
    // Get the current SSL configuration of the socket
    QSslConfiguration sslConfiguration;

    // Add the CA certificates
    sslConfiguration.setCaCertificates(caCertificates);

    // Set the SSL private key to the configuration
    sslConfiguration.setPrivateKey(sslKey);

    // Apply the modified SSL configuration to the socket
    sslSocket.setSslConfiguration(sslConfiguration);

    //connect
    sslSocket.connectToHostEncrypted(hostName, port);


    //def 30 sek
    if (sslSocket.waitForEncrypted(30000))    // Wait until encrypted connection is established or until 30 seconds elapse

    {
        qDebug() << "Connected";
        // Send message to the server
        sslSocket.write(xmlContent.toUtf8());


        if (sslSocket.waitForBytesWritten(30000))    // Wait until message is sent
                    qDebug() << "Message sent";
                else
                    qDebug().nospace() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";








        // Code to read data from the server
        if (sslSocket.waitForReadyRead(60000)) { // Wait up to 30s for data
            QByteArray responseData = sslSocket.readAll(); // Read available data
            qDebug() << "Received response:" << QString::fromUtf8(responseData);
        }
        else {
            qDebug() << "No response received within the timeout period.";
        }





    }
    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
    }

    this->deleteLater();

}
