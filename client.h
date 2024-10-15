#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QEventLoop>
#include <QTimer>
#include "jsonparsing.h"
#include "post_info.h"
#include "mainwindow.h"

class Client : public QObject
{
    Q_OBJECT

public:
    struct Info {
        QString MemberId;
        QString MemberPw;
        QString MemberName;
        int admin;
    };


    explicit Client(QObject *parent = nullptr);
    ~Client();

    void connectToServer(const QString &host, quint16 port); // 서버에 연결
    void sendMessage(const QString &message);
    void setFlag(int num);
    void sendLogin(QString id, QString pw);
    void addMembership(QString id, QString nickName, QString pw);
    void postGet(QString postNum);
    void writePost(QString title, QString nickname, QString detail);
    // void modifyPost(Post post)
    //     void deletePost(Post post)
    //     void writecomment(Post post, Comment comment.txt)
    //     void modifycomment(Post post, Comment comment.idx, Comment comment.txt)
    //     void deleteComment(Post post, Comment comment.idx)
    //     void subMembership(Info info)
    JsonParsing jsonParsing;
    QList<Post_info*> postInfos;

private slots:
    void onConnected();      // 서버에 연결되었을 때 호출
    void onReadyRead();      // 서버로부터 데이터 수신 시 호출
    void onDisconnected();   // 서버와 연결이 끊겼을 때 호출
    void onErrorOccurred(QAbstractSocket::SocketError socketError); // 에러 발생 시 호출

private:

    int flag;
    Info cliInfo;
    QStringList postTable;
    QString post;
    QTcpSocket *socket;  // TCP 소켓 객체
};

extern Client client;

#endif // CLIENT_H
