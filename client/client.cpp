#include "client.h"
#include <QHostAddress>
#include <QString>
#include <QDebug>

Client::Client(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
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

void Client::connectToServer(const QString &host, quint16 port)
{
    // 서버 IP와 포트로 연결 시도
    socket->connectToHost(QHostAddress(host), port);
    setFlag("3");
}

void Client::onConnected()
{
    // 서버에 연결되었을 때 호출됨
    qDebug() << "Connected to server!";
}

void Client::setFlag(int num)
{
    flag = num;
}


void Client::sendMessage(const QString &message)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        // 메시지를 서버로 전송
        socket->write(message.toUtf8());
        qDebug() << "Message sent to server:" << message;
    } else {
        qDebug() << "Socket is not connected!";
    }
}


void Client::sendLogin(QString id, QString pw)
{
    QString result = QString("%1:%2:%3").arg("1").arg(id).arg(pw);
    setFlag(1);
    sendMessage(result);
}

void Client::addMembership(QString id, QString nickName, QString pw)
{
    QString result = QString("%1:%2:%3").arg("2").arg(id).arg(pw);
    setFlag(2);
    sendMessage(result);
}

void Client::postGet(QString postNum)
{
    QString result = QString("%1:%2").arg("3").arg(postNum);
    setFlag(4);
    sendMessage(result);
}

void Client::writePost(QString title, QString nickname, QString detail)
{
    QString result = QString("%1:%2:%3").arg("5").arg(nickname).arg(detail);
    setFlag(5);
    sendMessage(result);
}

void Client::modifyPost(Post post)
{
    QString result = QString("%1:%2:%3").arg("6").arg().arg(detail);
    setFlag(6);
    sendMessage(result);
}

void Client::deletePost(Post post)
{
    QString result = QString("%1:%2:%3").arg("7").arg(nickname).arg(detail);
    setFlag(7);
    sendMessage(result);
}

void Client::writecomment(Post post, Comment comment.txt)
{
    QString result = QString("%1:%2:%3").arg("8").arg(nickname).arg(detail);
    setFlag(8);
    sendMessage(result);
}

void Client::modifycomment(Post post, Comment comment.idx, Comment comment.txt)
{
    QString result = QString("%1:%2:%3").arg("9").arg(nickname).arg(detail);
    setFlag(9);
    sendMessage(result);
}

void Client::deleteComment(Post post, Comment comment.idx)
{
    QString result = QString("%1:%2:%3").arg("10").arg(nickname).arg(detail);
    setFlag(10);
    sendMessage(result);
}

void Client::outMembership(Info info)
{
    QString result = QString("%1:%2:%3").arg("11").arg(info.MemberId).arg(info.MemberPw);
    setFlag(11);
    sendMessage(result);
}





void Client::onReadyRead()
{
    // 서버로부터 데이터가 수신되었을 때 호출됨
    QByteArray data = socket->readAll();
    qDebug() << "Received from server:" << QString::fromUtf8(data);
    QString datas = QString::fromUtf8(data);
    QStringList parsedData = datas.split('\n'); // QString datats[]
    switch (flag) {
    case 1: // tryLogin
        if (parsedData[0] == "-1") {
            qDebug() << "ID Wrong!";
            // IDWRONG SIG
        } else if (parsedData[0] == "-2") {
            qDebug() << "PW Wrong!";
            // PWWRONG SIG
        } else {
            qDebug() << "login success!";
            cliInfo.MemberId = parsedData[0];
            cliInfo.MemberPw = parsedData[1];
            cliInfo.MemberName = parsedData[2];
            cliInfo.admin = parsedData[3];
        }
        break;

    case 2: // setMembership
        if (parsedData[0] == "-1") {
            qDebug() << "ID Overlap";
            // 닉네임 중복
        } else if (parsedData[0] == "-2") {
            qDebug() << "your our member!!";
            // 닉네임 중복
        } else {
            qDebug() << "membership error";
        }
        break;

    case 3: // allpostGet
        if (parsedData[0] == "0") {
            qDebug() << "AllpostGet error";
        } else {
            postTable = std::move(parsedData);
        }
        break;

    case 4: // postGet
        if (parsedData[0] == "0") {
            qDebug() << "postGet error";
        } else {
            post = parsedData[0];
        }
        break;

    case 5: // WritePost
        if (parsedData[0] == "0") {
            qDebug() << "WritePost error";
        } else if (parsedData[0] == "1") {
            bool ok = true;
            int id = parsedData[0].toInt(&ok); // ??? id 어디에 쓸지??
            // 추가 처리가 필요할 수 있습니다.
        }
        break;

    case 6: // modifyPost
        if (parsedData[0] == "0") {
            qDebug() << "modifyPost error";
        } else if (parsedData[0] == "1") {
            qDebug() << "modifyPost success";
        }
        break;

    case 7: // deletePost
        if (parsedData[0] == "0") {
            qDebug() << "deletePost error";
        } else if (parsedData[0] == "1") {
            qDebug() << "deletePost success";
        }
        break;

    case 8: // Writecomment
        if (parsedData[0] == "0") {
            qDebug() << "error";
        } else if (parsedData[0] == "1") {
            qDebug() << "success";
        }
        break;

    case 9: // modifycomment
        if (parsedData[0] == "0") {
            qDebug() << "error";
        } else if (parsedData[0] == "1") {
            qDebug() << "success";
        }
        break;

    case 10: // deleteComment
        if (parsedData[0] == "0") {
            qDebug() << "error";
        } else if (parsedData[0] == "1") {
            qDebug() << "success";
        }
        break;

    case 11: // outMembership
        if (parsedData[0] == "-1") {
            qDebug() << "Id Wrong";
        } else if (parsedData[0] == "-2") {
            qDebug() << "Pw Wrong";
        } else if (parsedData[0] == "0") {
            qDebug() << "success_out";
        }
        break;

    default:
        qDebug() << "Unknown flag value!";
        break;
    }

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
