#ifndef CLIENT_H
#define CLIENT_H

#include <QEventLoop>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTimer>
#include "comment.h"
#include "introview.h"
#include "jsonparsing.h"
#include "mainwindow.h"
#include "post_info.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Info cliInfo;
    explicit Client(QObject *parent = nullptr);
    ~Client();
    int chkError();
    void connectToServer(const QString &host, quint16 port); // 서버에 연결
    void setFlag(int num);                                   // 비동기식 통신의 Flag 설정
    void sendMessage(const QString &message);                // 메시지 전송
    void sendLogin(QString id, QString pw);                  // 로그인시 로그인정보
    void addMembership(QString id, QString name, QString nickName, QString pw);
    void postGet(QString postNum);
    void writePost(QString title, QString detail);
    void modifyPost(Post_info post);
    void deletePost(Post_info post);
    void writeComment(comment com);
    void modifyComment(Post_info post, comment com);
    void deleteComment(comment com);
    void subMembership(QString id, QString pw);
    void uploadFile(QString fileName);
    void downLoadFile(QString fileName);
    void sendLogout();
    void setNowPostInfo(int id);

    Post_info *getNowPostInfo();
    void setNowPostInfo();

    JsonParsing jsonParsing;
    // IntroView *intro;
    QList<Post_info *> postInfos;

private slots:
    void onConnected();    // 서버에 연결되었을 때 호출
    void onReadyRead();    // 서버로부터 데이터 수신 시 호출
    void onDisconnected(); // 서버와 연결이 끊겼을 때 호출
    void onErrorOccurred(QAbstractSocket::SocketError socketError); // 에러 발생 시 호출
signals:
    void allPostgetFinished();

private:
    int flag;

    QStringList postTable;
    QString post;
    QTcpSocket *socket; // TCP 소켓 객체
    int status;
    Post_info *nowPost;
};

extern Client client;

#endif // CLIENT_H
