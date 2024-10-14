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
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("plz, enter the user id/pw."));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QLineEdit *idField = new QLineEdit(&dialog);
    form.addRow("ID", idField);
    QLineEdit *pwField = new QLineEdit(&dialog);
    form.addRow("PW", pwField);
    // QLineEdit *repwField = new QLineEdit(&dialog);
    // form.addRow("rePW", repwField);
    // fields << idField << pwField << repwField;
    fields << idField << pwField;

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal,
                               &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QLineEdit *idField = fields[0];
        QLineEdit *pwField = fields[1];
        // QLineEdit *repwField = fields[2];

        if (idField->text() == "" || pwField->text() == "") {
            util.showErrorMsg(this, "모든 항목을 채워주세요!");
            return;
        }
        // // 중복 아이디체크
        // bool isExistID = util.findID("user_info.txt", idField->text());
        // if (isExistID) {
        //     util.showErrorMsg(this, "이미 존재하는 아이디입니다.");
        //     return;
        // }
        // // 비밀번호 확인 체크
        // if (pwField->text() == repwField->text()) {
        //     util.writeFile("user_info.txt", idField->text() + ";" + pwField->text() + ":\n");
        // } else {
        //     util.showErrorMsg(this, "비밀번호를 확인해주세요.");
        //     return;
        // }
        // 회원가입 성공
    }
}

void MainWindow::startLogout()
{
    qDebug("startLogout");
}

void MainWindow::startSign()
{
    qDebug("startSign");
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Sign up"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QLineEdit *idField = new QLineEdit(&dialog);
    form.addRow("ID", idField);
    QLineEdit *pwField = new QLineEdit(&dialog);
    form.addRow("PW", pwField);
    QLineEdit *repwField = new QLineEdit(&dialog);
    form.addRow("rePW", repwField);
    fields << idField << pwField << repwField;

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal,
                               &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QLineEdit *idField = fields[0];
        QLineEdit *pwField = fields[1];
        QLineEdit *repwField = fields[2];

        if (idField->text() == "" || pwField->text() == "" || repwField->text() == "") {
            util.showErrorMsg(this, "모든 항목을 채워주세요!");
            return;
        }
        // // 중복 아이디체크
        // bool isExistID = util.findID("user_info.txt", idField->text());
        // if (isExistID) {
        //     util.showErrorMsg(this, "이미 존재하는 아이디입니다.");
        //     return;
        // }
        // // 비밀번호 확인 체크
        // if (pwField->text() == repwField->text()) {
        //     util.writeFile("user_info.txt", idField->text() + ";" + pwField->text() + ":\n");
        // } else {
        //     util.showErrorMsg(this, "비밀번호를 확인해주세요.");
        //     return;
        // }
        // 회원가입 성공
    }
}


void MainWindow::startExit()
{
    qDebug("startExit");
    exit(0);
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
    signAct = util.makeAction("",
                                "회원가입(S)",
                                "Ctrl+S",
                                "회원가입합니다.",
                                this,
                                SLOT(startSign()));
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
        toolBar->addSeparator();
        toolBar->addAction(signAct);
    }
    toolBar->addAction(exitAct);
    toolBar->addSeparator();
}

void MainWindow::initMain()
{
    intro = new IntroView(this);
    setCentralWidget(intro);
    intro->initIntro();
}

void MainWindow::goToPost()
{
    intro->close();
    postView = new PostView(this);
    setCentralWidget(postView);

}
