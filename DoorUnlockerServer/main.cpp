#include <QCoreApplication>
#include "secureserver.h"
#include "debugaction.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SecureServer sserver;

    sserver.setAction(DebugAction::getInstance());
    sserver.setPKeyPassPhrase("123456789");
    sserver.setPKeyPath(":/certs/rpi.key");
    sserver.setLocalCertificate(":/certs/rpi.crt");
    sserver.setCAPath(":/certs/rootCA.crt");

    sserver.start();
    return a.exec();
}
