#include "mainwindow.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    signAct
        = util.makeAction("", "회원가입(S)", "Ctrl+S", "회원가입합니다.", this, SLOT(startSign()));
    exitAct = util.makeAction("",
                              "종료(Q)",
                              "Ctrl+Q",
                              "회원을 새롭게 추가합니다.",
                              this,
                              SLOT(startExit()));

    initToolbar(0);
}

MainWindow::~MainWindow() {
    client.sendLogout();
}

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
    pwField->setEchoMode(QLineEdit::Password);
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

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, [&]() {
        QString id = idField->text(); // 여기에 실제 id 값을 넣으세요
        QString pw = pwField->text(); // 여기에 실제 pw 값을 넣으세요

        if (id == "" || pw == "") {
            util.showErrorMsg(this, "모든 항목을 채워주세요!");
            id = "\n";
            pw = "\n";
            return;
        }
        client.sendLogin(id, pw);
        if (client.chkError() == -1) {
            util.showErrorMsg(this, "잘못된 아이디 입니다.");
        } else if (client.chkError() == -2) {
            util.showErrorMsg(this, " 잘못된 비밀번호 입니다.");
        } else {
            util.showErrorMsg(this, " 로그인  성공?~");
            dialog.accept();
            initToolbar(1);
        }
    });
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    dialog.exec();
}

void MainWindow::startLogout()
{
    qDebug("startLogout");
    client.sendLogout();
    initToolbar(0);
    util.showErrorMsg(this, "로그 아웃 되었습니다!");
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
    QLineEdit *nickField = new QLineEdit(&dialog);
    form.addRow("Nickn", nickField);
    QLineEdit *nameField = new QLineEdit(&dialog);
    form.addRow("Name", nameField);
    QLineEdit *pwField = new QLineEdit(&dialog);
    pwField->setEchoMode(QLineEdit::Password);
    form.addRow("PW", pwField);
    QLineEdit *repwField = new QLineEdit(&dialog);
    repwField->setEchoMode(QLineEdit::Password);
    form.addRow("rePW", repwField);
    fields << idField << pwField << repwField;

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal,
                               &dialog);
    QPushButton *memberInButton = new QPushButton("회원 탈퇴", &dialog);
    buttonBox.addButton(memberInButton, QDialogButtonBox::ActionRole);
    form.addRow(&buttonBox);

    QObject::connect(memberInButton, &QPushButton::clicked, [&]() {
        // Apply 버튼을 눌렀을 때의 동작
        QString id = idField->text();
        QString pw = pwField->text();
        if (id.isEmpty() || pw.isEmpty()) {
            util.showErrorMsg(this, "ID, PW 항목을 채워주세요!");
            return;
        }
        client.subMembership(id, pw);
        if (client.chkError() == -1) {
            util.showErrorMsg(this, "잘못된 아이디 입니다.");
        } else if (client.chkError() == -2) {
            util.showErrorMsg(this, "잘못된 비밀번호 입니다.");
        } else {
            util.showErrorMsg(this, "회원탈퇴에 성공하였습니다.");
            dialog.accept();
        }
    });

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, [&]() {
        QString id = idField->text(); // 여기에 실제 id 값을 넣으세요
        QString pw = pwField->text(); // 여기에 실제 pw 값을 넣으세요
        QString name = nameField->text();
        QString nickname = nickField->text();
        QString repw = repwField->text();

        if (id.isEmpty() || pw.isEmpty() || repw.isEmpty() || nickname.isEmpty() || name.isEmpty()) {
            util.showErrorMsg(this, "항목을 채워주세요!");
            return;
        }
        if (pw != repw) {
            util.showErrorMsg(this, "비밀번호가 일치하지 않습니다.");
            return;
        }
        client.addMembership(id, name, nickname, pw);
        if (client.chkError() == 0) {
            util.showErrorMsg(this, "잘못된 아이디 입니다.");
        } else {
            util.showErrorMsg(this, "회원 가입 성공.");
            dialog.accept();
        }
    });
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    dialog.exec();
}

void MainWindow::startExit()
{
    client.sendLogout();
    qDebug("startExit");
    exit(0);
}

// CUSTOM

void MainWindow::initToolbar(int session)
{
    toolBar->clear();
    qDebug() << client.cliInfo.MemberId;

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
    qDebug() << "initMain";
    qDebug() << client.postInfos.size();
    intro = new IntroView(this);
    setCentralWidget(intro);
    intro->initIntro();
}

void MainWindow::goToPost(int index)
{
    // if (client.cliInfo.rank < 1) {
    //     util.showErrorMsg(this, "권한이 없습니다.");
    //     return;
    // }
    intro->close();
    postView = new PostView(this);
    postView->postviewInit(client.postInfos[index]->title,
                           client.postInfos[index]->nick,
                           client.postInfos[index]->rtime,
                           "image2",
                           client.postInfos[index]->contents,
                           client.postInfos[index]->id);
    setCentralWidget(postView);
}

void MainWindow::goToWrite()
{
    // if (client.cliInfo.rank < 1) {
    //     util.showErrorMsg(this, "권한이 없습니다.");
    //     return;
    // }
    intro->close();
    writeView = new WriteView(this);
    // postView->postviewInit(client.postInfos[index]->title,client.postInfos[index]->nick,"2024/10/17","image2",client.postInfos[index]->contents,client.postInfos[index]->id);
    setCentralWidget(writeView);
}
