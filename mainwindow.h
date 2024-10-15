#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QLabel>
#include <QMainWindow>
#include <QToolBar>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "introview.h"
#include "postview.h"
#include "util.h"

class IntroView;  // 전방 선언 추가

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *dockLabel;
    QDockWidget *dock;
    QToolBar *toolBar;
    QAction *loginAct;
    QAction *logoutAct;
    QAction *signAct;
    QAction *exitAct;
    void initToolbar(int session); // 세션있음 1 , 로그인필요 0

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMain();
    void goToPost();
    Util util;
    PostView *postView;
    int toolbarHeight;
    IntroView *intro;

public slots:
    void startLogin();
    void startLogout();
    void startSign();
    void startExit();
};
#endif // MAINWINDOW_H
