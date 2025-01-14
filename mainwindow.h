#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QDockWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QToolBar>
#include "introview.h"
#include "postview.h"
#include "util.h"
#include "writeview.h"

class IntroView; // 전방 선언 추가
class PostView;  // 전방 선언 추가
class WriteView; // 전방 선언 추가

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
    void goToPost(int index, int flag); // flag 0 인트로에서 이동 / 1 편집 완료
    void goToWrite(int index);          // index -1 글쓰기 / 그 외 게시글편집
    Util util;
    PostView *postView;
    WriteView *writeView;
    int toolbarHeight;
    IntroView *intro;

public slots:
    void startLogin();
    void startLogout();
    void startSign();
    void startExit();
};
#endif // MAINWINDOW_H
