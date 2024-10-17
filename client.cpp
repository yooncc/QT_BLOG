#include "client.h"
#include <QHostAddress>
#include <QString>
#include <QDebug>


Client client;

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

int Client::chkError()
{
    return status;
}

void Client::connectToServer(const QString &host, quint16 port)
{
    // 서버 IP와 포트로 연결 시도
    socket->connectToHost(QHostAddress(host), port);
    setFlag(3);
    sendMessage("3:1");
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
    socket->write(message.toUtf8());
    QEventLoop loop;

    // readyRead 시그널이 발생하면 이벤트 루프 종료
    connect(socket, &QTcpSocket::readyRead, &loop, &QEventLoop::quit);

    // 타이머를 설정하여 대기 시간이 너무 길지 않도록 함 (5초 대기)
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(5000);  // 타임아웃 시간 설정

    // 응답 또는 타임아웃까지 대기
    loop.exec();

    // 데이터 수신 후 처리
    if (socket->bytesAvailable()) {
        QByteArray data = socket->readAll();
        qDebug() << "Received response:" << data;
    } else {
        qDebug() << "No response received (timeout).";
    }
}


void Client::sendLogin(QString id, QString pw)
{
    QString result = QString("%1:%2:%3").arg("1").arg(id).arg(pw);
    setFlag(1);
    sendMessage(result);
}

void Client::addMembership(QString id, QString name, QString nickName, QString pw)
{
    QString result = QString("%1:%2:%3:%4:%5").arg("2").arg(id).arg(name).arg(nickName).arg(pw);
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

// void Client::modifyPost(Post post)
// {
//     QString result = QString("%1:%2:%3").arg("6").arg().arg(detail);
//     setFlag(6);
//     sendMessage(result);
// }

// void Client::deletePost(Post post)
// {
//     QString result = QString("%1:%2:%3").arg("7").arg(nickname).arg(detail);
//     setFlag(7);
//     sendMessage(result);
// }

// void Client::writecomment(Post post, Comment comment.txt)
// {
//     QString result = QString("%1:%2:%3").arg("8").arg(nickname).arg(detail);
//     setFlag(8);
//     sendMessage(result);
// }

// void Client::modifycomment(Post post, Comment comment.idx, Comment comment.txt)
// {
//     QString result = QString("%1:%2:%3").arg("9").arg(nickname).arg(detail);
//     setFlag(9);
//     sendMessage(result);
// }

// void Client::deleteComment(Post post, Comment comment.idx)
// {
//     QString result = QString("%1:%2:%3").arg("10").arg(nickname).arg(detail);
//     setFlag(10);
//     sendMessage(result);
// }

void Client::subMembership(QString id, QString pw)
{
    QString result = QString("%1:%2:%3").arg("11").arg(id).arg(pw);
    setFlag(11);
    qDebug() << result;
    sendMessage(result);
}


void Client::setLogout()
{
    client.cliInfo = {"", "", "", "", 0};
}


void Client::onReadyRead()
{
    // 서버로부터 데이터가 수신되었을 때 호출됨
    QByteArray data = socket->readAll();
    QString datas = QString::fromUtf8(data);
    QStringList parsedData = datas.split('\n'); // QString datats[]
    bool ok = true;
    switch (flag) {
    case 1: // tryLogin
        status = parsedData[0].toInt(&ok);
        if (parsedData[0] == "-1" || parsedData[0] == "-2") {
            qDebug() << "ID Wrong!";
        }

        else {
            qDebug() << "login success!";
            JsonParsing jsondata;
            Info parseData = jsondata.parseCliInfo(data);
            client.cliInfo = parseData;
        }
        break;

    case 2: // setMembership
        status = parsedData[0].toInt(&ok);
        if (parsedData[0] == "0") {
            qDebug() << "ID or nickname is Overlap";
            // 닉네임 중복
        } else if (parsedData[0] == "1") {
            qDebug() << "your our member!!";
            // 회원가입 성공
        } else {
            qDebug() << "membership error";
        }
        break;

    case 3: // allpostGet
        if (parsedData[0] == "0") {
            qDebug() << "AllpostGet error";
        } else {
            postTable = std::move(parsedData);
            for(int i = 0; i < postTable.size(); i++)
            {
                QByteArray postData = postTable[i].toUtf8();
                if (postData.isEmpty())
                    continue;

                Post_info* postInfo = jsonParsing.parsePost(postData);
                postInfos.append(postInfo);
                qDebug() << "clients " << postInfos.size();
            }
        }
        break;

    case 4: // postGet
        if (parsedData[0] == "0") {
            qDebug() << "postGet error";
        } else {
            post = parsedData[0];
        }
        break;

    // case 5: // WritePost
    //     if (parsedData[0] == "0") {
    //         qDebug() << "WritePost error";
    //     } else if (parsedData[0] == "1") {
    //         bool ok = true;
    //         int id = parsedData[0].toInt(&ok); // ??? id 어디에 쓸지??
    //         // 추가 처리가 필요할 수 있습니다.
    //     }
    //     break;

    // case 6: // modifyPost
    //     if (parsedData[0] == "0") {
    //         qDebug() << "modifyPost error";
    //     } else if (parsedData[0] == "1") {
    //         qDebug() << "modifyPost success";
    //     }
    //     break;

    // case 7: // deletePost
    //     if (parsedData[0] == "0") {
    //         qDebug() << "deletePost error";
    //     } else if (parsedData[0] == "1") {
    //         qDebug() << "deletePost success";
    //     }
    //     break;

    // case 8: // Writecomment
    //     if (parsedData[0] == "0") {
    //         qDebug() << "error";
    //     } else if (parsedData[0] == "1") {
    //         qDebug() << "success";
    //     }
    //     break;

    // case 9: // modifycomment
    //     if (parsedData[0] == "0") {
    //         qDebug() << "error";
    //     } else if (parsedData[0] == "1") {
    //         qDebug() << "success";
    //     }
    //     break;

    // case 10: // deleteComment
    //     if (parsedData[0] == "0") {
    //         qDebug() << "error";
    //     } else if (parsedData[0] == "1") {
    //         qDebug() << "success";
    //     }
    //     break;

    case 11: // outMembership
        status = parsedData[0].toInt(&ok);
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
