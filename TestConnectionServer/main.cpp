#include <QCoreApplication>
#include "server.h"

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    Server server;
    if (server.listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server started";
    }
    else {
        qDebug() << "Server failed to start";
    }

    return a.exec();
}
