#include "postview.h"
#include "mainwindow.h"

PostView::PostView(QWidget *parent)
    : QWidget{parent}
{
    int screenHeight = parent->height() - (((MainWindow *) (this->parent()))->toolbarHeight);
    viewOriginX = (parent->width()/7) * 2;

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // 스크롤 영역이 동적으로 크기 조정 가능하게 설정
    scrollArea->setGeometry(QRect(viewOriginX,0,parent->width()-(viewOriginX*2),screenHeight));
    // scrollArea->setGeometry(QRect(0,0,parent->width(),screenHeight));
    scrollArea->setStyleSheet("background-color: lightgray;");

    backBtn = util.makePushButton(this, "back", "", 8, false, "");
    backBtn->setGeometry((QRect(50,50,50,50)));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backAct()));
}


void PostView::backAct()
{
    qDebug("backAct");
    ((MainWindow*)(this->parent()))->initMain();
}

void PostView::cmtAct()
{
    qDebug("cmtAct");
    ((MainWindow*)(this->parent()))->initMain();
}

// void PostView::Download()
// {
//     client.downLoadFile();
// }

void PostView::postviewInit(QString title, QString nick, QString date, QString image, QString contents, int id) {

    this->postId = id;
    scrollWidget = new QWidget;

    int offsetY = 100;
    int width = scrollArea->width();

    titleLabel = new QLabel(scrollWidget);
    titleLabel->setText(title);
    titleLabel->setStyleSheet("color: black; font-weight: bold; font-size: 32px;");
    titleLabel->adjustSize();
    titleLabel->setGeometry(QRect(8,offsetY,width-16,titleLabel->height()));

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
    nickLabel->setGeometry(QRect(8,offsetY,nickLabel->width(),nickLabel->height()));

    // 다운로드 버튼
    // downLoadBtn = util.makePushButton(scrollWidget, "다운로드", 11, false, "");
    // downLoadBtn->setGeometry((QRect(8,offsetY+4,50,20));
    // connect(cmtBtn, SIGNAL(clicked()), this, SLOT(Download()));

    dateLabel = new QLabel(scrollWidget);
    dateLabel->setText(date);
    dateLabel->setStyleSheet("color: black; font-size: 14px;");
    dateLabel->setGeometry(QRect(nickLabel->x()+nickLabel->width(),offsetY,dateLabel->width(),nickLabel->height()));

    offsetY += nickLabel->height() + 8;

    imageLabel = new QLabel(scrollWidget);
    imageLabel->setText(image);
    imageLabel->setGeometry(QRect(8,offsetY,width-16,200));
    imageLabel->setStyleSheet("background-color: yellow;");

    offsetY += imageLabel->height() + 16;

    contentsLabel = new QLabel(scrollWidget);
    contentsLabel->setText(contents);
    contentsLabel->setStyleSheet("background-color: pink; color: black;font-size: 13px; font-weight: bold; ");
    contentsLabel->adjustSize();
    contentsLabel->setGeometry(QRect(8,offsetY,width-16,contentsLabel->height()));

    offsetY += contentsLabel->height() + 16;

    QLabel *border = new QLabel(scrollWidget);
    border->setGeometry(QRect(8,offsetY,width-16,1));
    border->setStyleSheet("background-color: black;");

    offsetY += border->height() + 8;

    commentEdit = new QTextEdit(scrollWidget);
    commentEdit->setGeometry(QRect(8,offsetY,width-74,50));
    commentEdit->setStyleSheet("background-color: white; color: black;font-size: 13px;");

    cmtBtn = util.makePushButton(scrollWidget, "입력", "", 11, false, "");
    cmtBtn->setGeometry((QRect(commentEdit->x()+commentEdit->width()+8,offsetY,50,50)));
    connect(cmtBtn, SIGNAL(clicked()), this, SLOT(cmtAct()));



    offsetY += cmtBtn->height() + 16;

    scrollWidget->setFixedHeight(offsetY);
    scrollArea->setWidget(scrollWidget);


}
