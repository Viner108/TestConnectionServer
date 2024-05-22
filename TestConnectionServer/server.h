#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QPointF>
#include "mydto.h"

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);

public slots:
    void onNewConnection();
    void onReadyRead();

private:
    QPointF circlePosition;

    QPointF calculateNewPosition();
};

#endif // SERVER_H
