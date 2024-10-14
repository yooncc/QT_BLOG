#include "client.h"
#include <QHostAddress>
#include <QDebug>
#include <QString>
#include <Qvector>

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    // 소켓과 관련된 시그널과 슬롯 연결
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &Client::onErrorOccurred);
}

Client::~Client()
{
    // 소켓 삭제
    if (socket) {
        socket->close();
        delete socket;
    }
}
QStringList Client::getpostList()
{
    return postList;
}

void Client::connectToServer(const QString &host, quint16 port)
{
    // 서버 IP와 포트로 연결 시도
    socket->connectToHost(QHostAddress(host), port);
}

void Client::sendMessage(const QString &message)
{
    socket->write(message.toUtf8());
}

void Client::onConnected()
{
    // 서버에 연결되었을 때 호출됨
    qDebug() << "Connected to server!";
    this->initPost();
}

void Client::initPost()
{
    this->sendMessage("3:1");
    QByteArray data = socket->readAll();

    QString dataString = QString::fromUtf8(data);
    postList = dataString.split("\n");

    qDebug() << dataString << "\n";
    for (int i=0;i<postList.size();i++) {
        qDebug() << postList[i] << "\n";
    }

}

// void Client::cmpMember()
// {
//     socket->write("1");
//     QByteArray data = socket->readAll();
//     QString dataString = QString::fromUtf8(data);
//     QStringList LoginList = dataString.split("\n");
//     for(int i = 0; i < LogList; i+=2)
//     {
//         if(LogintList[i]=="id" && LoginList[i+1]=="pw")
//         {
//             id = LoginList[i];
//             pw = LoginList[i+1];
//         }
//     }
// }

void Client::onReadyRead()
{
    // 서버로부터 데이터가 수신되었을 때 호출됨
    qDebug() << "Received from server:";
}

void Client::onDisconnected()
{
    // 서버와의 연결이 끊겼을 때 호출됨
    qDebug() << "Disconnected from server.";
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    // 소켓에서 에러가 발생했을 때 처리
    qDebug() << "Socket error:" << socket->errorString();
}
