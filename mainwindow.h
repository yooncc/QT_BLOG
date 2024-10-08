#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QLabel>
#include <QMainWindow>
#include <QToolBar>
#include "introview.h"
#include "util.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *dockLabel;
    QDockWidget *dock;
    QToolBar *toolBar;
    QAction *loginAct;
    QAction *logoutAct;
    QAction *exitAct;
    void initToolbar(int session); // 세션있음 1 , 로그인필요 0

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMain();
    Util util;
    IntroView *intro;
    int toolbarHeight;

public slots:
    void startLogin();
    void startLogout();
    void startExit();
};
#endif // MAINWINDOW_H
