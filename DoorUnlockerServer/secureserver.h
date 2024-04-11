#ifndef SECURESERVER_H
#define SECURESERVER_H

#include <QObject>
#include <QSslServer>

#include "abstractaction.h"
class SecureServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString CAPath READ CAPath WRITE setCAPath FINAL REQUIRED)
    Q_PROPERTY(QString pKeyPath READ pKeyPath WRITE setPKeyPath FINAL REQUIRED)
    Q_PROPERTY(QString pKeyPassPhrase READ pKeyPassPhrase WRITE setPKeyPassPhrase FINAL REQUIRED)
    Q_PROPERTY(QString localCertificate READ localCertificate WRITE setLocalCertificate FINAL REQUIRED)

private:
    AbstractAction* action = nullptr;
    QSslServer* server;
    QSslConfiguration sslConfig;

    QString m_CAPath;

    QString m_pKeyPassPhrase;

    QString m_pKeyPath;

    QString m_localCertificate;

public:
    explicit SecureServer(QObject *parent = nullptr);

    QString CAPath() const;
    void setCAPath(const QString &newCAPath);

    QString pKeyPassPhrase() const;
    void setPKeyPassPhrase(const QString &newPKeyPassPhrase);

    QString pKeyPath() const;
    void setPKeyPath(const QString &newPKeyPath);

    QString localCertificate() const;
    void setLocalCertificate(const QString &newLocalCertificate);

    void setAction(AbstractAction* newAction);
    void start();
signals:

public slots:
    void connectionAvailable();
    void dataReceived();
    void error(const QList<QSslError> &err);
};

#endif // SECURESERVER_H
