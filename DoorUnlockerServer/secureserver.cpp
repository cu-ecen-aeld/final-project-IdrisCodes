#include "secureserver.h"
#include <QFile>
#include <QSslKey>

SecureServer::SecureServer(QObject *parent)
    : QObject{parent}
{
    server = new QSslServer(parent);
    connect(server,     &QSslServer::pendingConnectionAvailable,
            this,       &SecureServer::connectionAvailable);
}

QString SecureServer::CAPath() const
{
    return m_CAPath;
}

void SecureServer::setCAPath(const QString &newCAPath)
{
    m_CAPath = newCAPath;

    /* Set up root CA */
    QFile rootCaFile(m_CAPath);
    rootCaFile.open(QIODeviceBase::OpenModeFlag::ReadOnly);
    QSslCertificate ca_cert(rootCaFile.readAll());
    sslConfig.addCaCertificate(ca_cert);
}

QString SecureServer::pKeyPassPhrase() const
{
    return m_pKeyPassPhrase;
}

void SecureServer::setPKeyPassPhrase(const QString &newPKeyPassPhrase)
{
    m_pKeyPassPhrase = newPKeyPassPhrase;
}

QString SecureServer::pKeyPath() const
{
    return m_pKeyPath;
}

void SecureServer::setPKeyPath(const QString &newPKeyPath)
{
    m_pKeyPath = newPKeyPath;

    QFile key_file(m_pKeyPath);
    key_file.open(QIODeviceBase::OpenModeFlag::ReadOnly);
    QSslKey pkey(key_file.readAll(), QSsl::KeyAlgorithm::Rsa, QSsl::EncodingFormat::Pem,
                 QSsl::PrivateKey, m_pKeyPassPhrase.toUtf8());
    sslConfig.setPrivateKey(pkey);

}

QString SecureServer::localCertificate() const
{
    return m_localCertificate;
}

void SecureServer::setLocalCertificate(const QString &newLocalCertificate)
{
    m_localCertificate = newLocalCertificate;

    QFile cert_file(m_localCertificate);
    cert_file.open(QIODeviceBase::OpenModeFlag::ReadOnly);
    QSslCertificate local_cert(cert_file.readAll());
    sslConfig.setLocalCertificate(local_cert);
}

void SecureServer::setAction(AbstractAction* newAction)
{
    if(newAction != nullptr)
        action = newAction;
}

void SecureServer::start()
{
    sslConfig.setProtocol(QSsl::TlsV1_2OrLater);

    server->setSslConfiguration(sslConfig);
    server->listen(QHostAddress::Any, 4433);
    qDebug() << "Server started listening on port 4433";
}

void SecureServer::connectionAvailable()
{
    auto socket{server->nextPendingConnection()};
    if(socket != nullptr)
    {
        qDebug() << "A new socket was successfully created";
        QObject::connect(socket,    &QSslSocket::readyRead,
                        this,       &SecureServer::dataReceived);

        QObject::connect(dynamic_cast<QSslSocket*>(socket),    &QSslSocket::sslErrors,
                         this,      &SecureServer::error);
    }
    else
    {
        qDebug() << "Null pointer";
    }
}

void SecureServer::dataReceived()
{
    QSslSocket* clientSocket = qobject_cast<QSslSocket*>(sender());
    qDebug() << "Received: " << clientSocket->readAll();
    clientSocket->write("Ack");
    if(action)
    {
        action->doAction();
    }
    clientSocket->disconnectFromHost();
}

void SecureServer::error(const QList<QSslError> &err)
{
    for(auto& item : err)
        qWarning() << err;
}
