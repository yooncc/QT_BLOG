#include "commentcell.h"

CommentCell::CommentCell(QWidget *parent)
    : QWidget{parent}
{
    QLabel* border1 = new QLabel(this);
    border1->setGeometry(QRect(0,0,1000,1));
    border1->setStyleSheet("background-color: black;");

    nickLabel = new QLabel(this);
    nickLabel->setStyleSheet("color: black; font-size: 14px;");
    nickLabel->setGeometry(QRect(8,1,0,29));

    contentsLabel = new QTextEdit(this);
    contentsLabel->setStyleSheet("color: black; font-size: 12px; border: none;");
    contentsLabel->setGeometry(QRect(8,30,0,50));

    QLabel* border2 = new QLabel(this);
    border2->setGeometry(QRect(0,79,1000,1));
    border2->setStyleSheet("background-color: black;");
}


void CommentCell::initComment(QString nick, QString contents) {
    this->nickLabel->setText(nick);
    this->contentsLabel->setText(contents);
}
