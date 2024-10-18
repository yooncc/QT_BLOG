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
#include "post_info.h"
#include "introview.h"
#include "comment.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Info cliInfo;
    explicit Client(QObject *parent = nullptr);
    ~Client();
    int chkError();
    void connectToServer(const QString &host, quint16 port); // 서버에 연결
    void sendMessage(const QString &message);
    void setFlag(int num);
    void sendLogin(QString id, QString pw);
    void addMembership(QString id, QString name, QString nickName, QString pw);
    void postGet(QString postNum);
    void writePost(QString title, QString nickname, QString detail);
    void setLogout();
    void modifyPost(Post_info post);
    void deletePost(Post_info post);
    void writecomment(comment com);
    void modifycomment(Post_info post, comment com);
    void deleteComment(Post_info post, comment com);
    void subMembership(QString id, QString pw);
    void

    Post_info getNowPostInfo();
    void setNowPostInfo();
    JsonParsing jsonParsing;
    // IntroView *intro;
    QList<Post_info*> postInfos;


private slots:
    void onConnected();      // 서버에 연결되었을 때 호출
    void onReadyRead();      // 서버로부터 데이터 수신 시 호출
    void onDisconnected();   // 서버와 연결이 끊겼을 때 호출
    void onErrorOccurred(QAbstractSocket::SocketError socketError); // 에러 발생 시 호출
signals:
    void allPostgetFinished();
private:

    int flag;

    QStringList postTable;
    QString post;
    QTcpSocket *socket;  // TCP 소켓 객체
    int status;
    Post_info nowPost;
};

extern Client client;

#endif // CLIENT_H
