#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void connectToServer(const QString &host, quint16 port); // 서버에 연결
    void sendMessage(const QString &message); // 서버로 메시지 전송

private slots:
    void onConnected();      // 서버에 연결되었을 때 호출
    void onReadyRead();      // 서버로부터 데이터 수신 시 호출
    void onDisconnected();   // 서버와 연결이 끊겼을 때 호출
    void onErrorOccurred(QAbstractSocket::SocketError socketError); // 에러 발생 시 호출

private:
    QTcpSocket *socket;  // TCP 소켓 객체
};

#endif // CLIENT_H
