#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;

    // 서버에 연결 (localhost의 1234 포트로 연결)
    client.connectToServer("127.0.0.1", 1234);
    client.sendFlag("Hello, Server!");
    // 서버로 메시지 전송 (연결 후 전송하도록 지연)

    return a.exec();
}
