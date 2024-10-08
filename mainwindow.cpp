#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initToolbar(0);

    // dockLabel = new QLabel("admin");
    // dockLabel->setAlignment(Qt::AlignRight);
    // dock = new QDockWidget(this);
    // dock->setTitleBarWidget(dockLabel);
    // addDockWidget(Qt::BottomDockWidgetArea, dock);
}

MainWindow::~MainWindow() {}

// SLOT FUNCTION
void MainWindow::startLogin()
{
    qDebug("startLogin");
}

void MainWindow::startLogout()
{
    qDebug("startLogout");
}

void MainWindow::startExit()
{
    qDebug("startExit");
}

// CUSTOM

void MainWindow::initToolbar(int session)
{
    toolBar = new QToolBar("toolbar", this);
    addToolBar(toolBar);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
    this->toolbarHeight = this->toolBar->height();

    loginAct = util.makeAction("",
                               "로그인(L)",
                               "Ctrl+L",
                               "로그인을 시작합니다.",
                               this,
                               SLOT(startLogin()));
    logoutAct = util.makeAction("",
                                "로그아웃(L)",
                                "Ctrl+L",
                                "로그아웃합니다.",
                                this,
                                SLOT(startLogout()));
    exitAct = util.makeAction("",
                              "종료(Q)",
                              "Ctrl+Q",
                              "회원을 새롭게 추가합니다.",
                              this,
                              SLOT(startExit()));

    if (session == 1) {
        toolBar->addAction(logoutAct);
        toolBar->addSeparator();
    } else {
        toolBar->addSeparator();
        toolBar->addAction(loginAct);
    }
    toolBar->addAction(exitAct);
    toolBar->addSeparator();
}

void MainWindow::initMain()
{
    intro = new IntroView(this);
    setCentralWidget(intro);
}
