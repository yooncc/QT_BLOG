#include "writeview.h"

WriteView::WriteView(QWidget *parent)
    : QWidget{parent}
{
    int screenHeight = parent->height() - (((MainWindow *) (this->parent()))->toolbarHeight);
    int viewOriginX = (parent->width()/7) * 2;

    QWidget* writePlace = new QWidget(this);
    writePlace->setGeometry(QRect(viewOriginX,0,parent->width()-(viewOriginX*2),screenHeight));
    writePlace->setStyleSheet("background-color: lightgray;");

    titleEdit = new QLineEdit(writePlace);
    titleEdit->setPlaceholderText("제목을 입력하세요.");
    titleEdit->setGeometry(QRect(8,50,writePlace->width()-16,50));
    titleEdit->setStyleSheet("background-color: white; color: black;font-size: 25px; font-weight: bold;");

    contentEdit = new QTextEdit(writePlace);
    contentEdit->setPlaceholderText("내용을 입력하세요.");
    contentEdit->setGeometry(QRect(8,120,writePlace->width()-16,screenHeight-120-120));
    contentEdit->setStyleSheet("background-color: white; color: black;font-size: 16px; font-weight: bold;");

    writeBtn = util.makePushButton(writePlace, "완료", "", 8, false, "");
    writeBtn->setGeometry((QRect(8,contentEdit->y()+contentEdit->height()+16,writePlace->width()-16,100)));
    connect(writeBtn, SIGNAL(clicked()), this, SLOT(writeAct()));

    backBtn = util.makePushButton(this, "back", "", 8, false, "");
    backBtn->setGeometry((QRect(50,50,50,50)));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backAct()));
}

void WriteView::backAct()
{
    qDebug("backAct");
    ((MainWindow*)(this->parent()))->initMain();
}

void WriteView::writeAct()
{
    qDebug("writeAct");

    if (titleEdit->text() == "" || contentEdit->toPlainText().isEmpty()) {
        util.showErrorMsg(this,"모든 항목을 채워주세요!");
        return;
    }
    qDebug() << titleEdit->text();
    qDebug() << contentEdit->toPlainText();
    ((MainWindow*)(this->parent()))->initMain();
}
