#include "server.h"

Server::Server(QObject* parent) : QTcpServer(parent), circlePosition(0, 0) {
    connect(this, &Server::newConnection, this, &Server::onNewConnection);
}

void Server::onNewConnection() {
    QTcpSocket* clientSocket = nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    qDebug() << "New client connected";
}

void Server::onReadyRead() {
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        QDataStream in(&data, QIODevice::ReadOnly);
        MyDTO dto;
        in >> dto;
        qDebug() << "Received DTO:" << dto.x << dto.y;

        // Calculate new position
        circlePosition = calculateNewPosition();

        // Send new position back to client
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << circlePosition.x() << circlePosition.y();
        clientSocket->write(block);
    }
}

QPointF Server::calculateNewPosition() {
    // Update the position for simplicity (e.g., move right by 10 units)
    circlePosition.setX(circlePosition.x() + 10);
    return circlePosition;
}
