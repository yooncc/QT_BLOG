#include <QApplication>
#include <QScreen>
#include "mainwindow.h"

#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    client.connectToServer("192.168.0.47", 8001);
    // client.connectToServer("127.0.0.1", 8001);
    // 서버로 메시지 전송 (연결 후 전송하도록 지연)

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    w.resize(screenWidth * 0.8, screenHeight * 0.8);
    w.show();
    w.initMain();
    return a.exec();
}
