#include "postview.h"
#include "mainwindow.h"

PostView::PostView(QWidget *parent)
    : QWidget{parent}
{
    int screenHeight = parent->height() - (((MainWindow *) (this->parent()))->toolbarHeight);
    viewOriginX = (parent->width() / 7) * 2;

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); // 스크롤 영역이 동적으로 크기 조정 가능하게 설정
    scrollArea->setGeometry(
        QRect(viewOriginX, 0, parent->width() - (viewOriginX * 2)+15, screenHeight));
    // scrollArea->setGeometry(QRect(0,0,parent->width(),screenHeight));
    scrollArea->setStyleSheet("background-color: lightgray;");

    backBtn = util.makePushButton(this, "back", "", 8, false, "");
    backBtn->setGeometry((QRect(50, 50, 50, 50)));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backAct()));
}

void PostView::backAct()
{
    qDebug("backAct");
    ((MainWindow *) (this->parent()))->initMain();
}

void PostView::cmtAct()
{
    qDebug("cmtAct");
    if (commentEdit->toPlainText() == "") {
        util.showErrorMsg(this,"댓글을 입력해주세요.");
        return;
    }
    // commentRenew();
    struct comment newComment;
    newComment.idx = client.postInfos[index]->comments->size();
    newComment.nick = client.cliInfo.MemberNickName;
    newComment.contents = commentEdit->toPlainText();

    client.writeComment(newComment, QString::number(this->postId));

    client.postInfos[index]->comments->append(newComment);

    scrollWidget->close();

    postviewInit(client.postInfos[index]->title,
                 client.postInfos[index]->nick,
                 client.postInfos[index]->rtime,
                 "image2",
                 client.postInfos[index]->contents,
                 client.postInfos[index]->id,
                 index);

}



void PostView::delAct()
{
    qDebug("delAct");
    client.deletePost(client.postInfos[index]);
    ((MainWindow *) (this->parent()))->initMain();
}

void PostView::modAct()
{
    qDebug("modAct");
    ((MainWindow *) (this->parent()))->goToWrite(this->index);
}

void PostView::cmtModAct(int index) {
    qDebug() << "cmtModAct";

    QDialog dialog(this);
    QFormLayout form(&dialog);
    // Add some text above the fields
    form.addRow(new QLabel("수정할 댓글을 입력해주세요."));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QLineEdit *contentsField = new QLineEdit(&dialog);
    form.addRow("",contentsField);
    fields << contentsField;

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal,
                               &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, [&]() {
        QString mContents = contentsField->text();
        if (mContents == "") {
            util.showErrorMsg(this, "수정할 댓글을 입력하세요!");
            return;
        }

        struct comment newCmt;
        newCmt.contents = mContents;
        newCmt.idx = client.postInfos[this->index]->comments->at(index).idx;
        newCmt.nick = client.postInfos[this->index]->comments->at(index).nick;

        client.postInfos[this->index]->comments->replace(index, newCmt);  // 바로 덮어쓰기

        client.modifyComment(client.postInfos[this->index],client.postInfos[this->index]->comments->at(index));

        scrollWidget->close();

        postviewInit(client.postInfos[this->index]->title,
                     client.postInfos[this->index]->nick,
                     client.postInfos[this->index]->rtime,
                     "image2",
                     client.postInfos[this->index]->contents,
                     client.postInfos[this->index]->id,
                     this->index);
        dialog.accept();
    });
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    dialog.exec();

}

void PostView::cmtDelAct(int index) {
    qDebug() << "cmtDelAct";
    myint = 1;
    client.postInfos[this->index]->comments->removeAt(index);

    scrollWidget->close();

    postviewInit(client.postInfos[this->index]->title,
                 client.postInfos[this->index]->nick,
                 client.postInfos[this->index]->rtime,
                 "image2",
                 client.postInfos[this->index]->contents,
                 client.postInfos[this->index]->id,
                 this->index);
}


void PostView::downloadFile()
{
    QString selectName = comboBox->currentText();
    qDebug() << "----fasdfasdfsdf" << selectName;
    client.downLoadFile(selectName);
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

void PostView::postviewInit(
    QString title, QString nick, QString date, QString image, QString contents, int id, int index)
{
    int offsetY = 100;
    int width = scrollArea->width()-15;

    if (nick == client.cliInfo.MemberNickName || client.cliInfo.rank > 1) {
        if (nick == client.cliInfo.MemberNickName) {
            modBtn = util.makePushButton(this, "modify", "", 8, false, "");
            modBtn->setGeometry((QRect(scrollArea->x()+width+50, 50, 50, 50)));
            connect(modBtn, SIGNAL(clicked()), this, SLOT(modAct()));
        }
        delBtn = util.makePushButton(this, "delete", "", 8, false, "");
        delBtn->setGeometry((QRect(scrollArea->x()+width+50, 116, 50, 50)));
        connect(delBtn, SIGNAL(clicked()), this, SLOT(delAct()));
    }

    // 다운로드 버튼
    downloadBtn = util.makePushButton(this, "다운로드", "",11, false, "");
    downloadBtn->setGeometry((QRect(scrollArea->x()+width+35,182,80,50)));
    connect(downloadBtn, SIGNAL(clicked()), this, SLOT(downloadFile()));



    std::vector<QString> fileNames = client.postInfos[index]->fileNames;
    if (!fileNames.empty())
    {
        QButtonGroup *buttonGroup = new QButtonGroup(this);
        comboBox = new QComboBox(this);
        comboBox->setGeometry(QRect(downloadBtn->x(), downloadBtn->y() + downloadBtn->height() + 8, 200, 30));
        // 파일 이름을 콤보박스에 추가
        for (const auto &fileName : fileNames) {

            comboBox->addItem(fileName);
        }
        // comboBox->setCurrentIndex(0);
    }

    // 첫 번째 파일을 기본 선택 (기본적으로 첫 번째 항목이 선택됨)


    this->postId = id;
    this->index = index;
    scrollWidget = new QWidget;
    titleLabel = new QLabel(scrollWidget);
    titleLabel->setText(title);
    titleLabel->setWordWrap(true);
    titleLabel->setStyleSheet("color: black; font-weight: bold; font-size: 32px;");
    titleLabel->adjustSize();
    titleLabel->setGeometry(QRect(8, offsetY, width - 16, titleLabel->height()));

    // titleLabel->setStyleSheet("background-color: blue;");

    offsetY += titleLabel->height() + 8;

    nickLabel = new QLabel(scrollWidget);
    QString nickStr = "작성자: ";
    nickStr.append(nick);
    nickStr.append(" · ");
    nickLabel->setText(nickStr);
    nickLabel->setStyleSheet("color: black;font-size: 14px; font-weight: bold;");
    nickLabel->adjustSize();
    // nickLabel->setGeometry(QRect(8,offsetY,width/2-8,20));
    nickLabel->setGeometry(QRect(8, offsetY, nickLabel->width(), nickLabel->height()));



    dateLabel = new QLabel(scrollWidget);
    dateLabel->setText(date);
    dateLabel->setStyleSheet("color: black; font-size: 14px;");
    dateLabel->adjustSize();
    dateLabel->setGeometry(QRect(nickLabel->x() + nickLabel->width(),
                                 offsetY,
                                 dateLabel->width(),
                                 nickLabel->height()));

    offsetY += nickLabel->height() + 8;

    imageLabel = new QLabel(scrollWidget);
    imageLabel->setGeometry(QRect(8, offsetY, width - 16, 200));
    QPixmap pixmap(image);
    if (pixmap.isNull()) {
        pixmap = QPixmap(":/veda_w.png");
    }
    imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatioByExpanding));

    offsetY += imageLabel->height() + 16;

    contentsLabel = new QLabel(scrollWidget);
    contentsLabel->setText(contents);
    contentsLabel->setStyleSheet(
        "color: black;font-size: 13px; font-weight: bold; border: none;");
    contentsLabel->adjustSize();
    contentsLabel->setWordWrap(true);
    contentsLabel->setGeometry(QRect(8, offsetY, width - 16, contentsLabel->height()));

    offsetY += contentsLabel->height() + 16;

    QLabel *border = new QLabel(scrollWidget);
    border->setGeometry(QRect(8, offsetY, width - 16, 1));
    border->setStyleSheet("background-color: black;");

    offsetY += border->height() + 8;

    commentEdit = new QTextEdit(scrollWidget);
    commentEdit->setGeometry(QRect(8, offsetY, width - 74, 50));
    commentEdit->setStyleSheet("background-color: white; color: black;font-size: 13px;");

    cmtBtn = util.makePushButton(scrollWidget, "입력", "", 11, false, "");
    cmtBtn->setGeometry((QRect(commentEdit->x() + commentEdit->width() + 8, offsetY, 50, 50)));
    connect(cmtBtn, SIGNAL(clicked()), this, SLOT(cmtAct()));

    offsetY += cmtBtn->height() + 16;

    QList<comment>* cmtArr = client.postInfos[index]->comments;
    if (cmtArr->size() > 0) {
        for (int i = 0 ; i<cmtArr->size(); i++) {
            CommentCell* commentCell = new CommentCell(scrollWidget);
            commentCell->nickLabel->setFixedWidth(width-16);
            commentCell->contentsLabel->setFixedWidth(width-16);
            commentCell->setGeometry(QRect(0,offsetY,width,80));
            commentCell->initComment(cmtArr->at(i), client.postInfos[index]);
            connect(commentCell, &CommentCell::delSignal, this, &PostView::cmtDelAct);
            connect(commentCell, &CommentCell::modSignal, this, &PostView::cmtModAct);
            offsetY += commentCell->height() + 16;
        }
    }

    scrollWidget->setFixedHeight(offsetY);

    scrollArea->setWidget(scrollWidget);

}
