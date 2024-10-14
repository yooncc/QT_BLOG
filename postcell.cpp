#include "postcell.h"

PostCell::PostCell(QWidget *parent)
    : QWidget{parent}
{
    int cellWidth = 260, cellHeight = 300, currentY = 0;

    QLabel* backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(QRect(0,0,cellWidth,cellHeight));
    backgroundLabel->setStyleSheet("background-color: lightblue;");

    imageLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    contentsLabel = new QLabel(this);
    dateLabel = new QLabel(this);
    commentLabel = new QLabel(this);
    profileLabel = new QLabel(this);
    nickLabel = new QLabel(this);
    likeLabel = new QLabel(this);


    imageLabel->setGeometry(QRect(0,currentY,cellWidth,cellHeight*0.35));
    imageLabel->setStyleSheet("background-color: lightgray; color: red;");
    currentY += imageLabel->height();

    titleLabel->setGeometry(QRect(0,currentY,cellWidth,cellHeight*0.1));
    titleLabel->setStyleSheet("background-color: white; color: black;");
    currentY += titleLabel->height();

    contentsLabel->setGeometry(QRect(0,currentY,cellWidth,cellHeight*0.3));
    contentsLabel->setStyleSheet("background-color: white; color: black;");
    currentY += contentsLabel->height();

    dateLabel->setGeometry(QRect(0,currentY,cellWidth/2,cellHeight*0.1));
    commentLabel->setGeometry(QRect(dateLabel->x()+dateLabel->width(),currentY,cellWidth/2,cellHeight*0.1));

    currentY += dateLabel->height();

    profileLabel->setGeometry(QRect(16,currentY,cellHeight*0.15,cellHeight*0.15));
    nickLabel->setGeometry(QRect(profileLabel->x()+profileLabel->width(),currentY,cellWidth/3,cellHeight*0.15));
    likeLabel->setGeometry(QRect(cellWidth-100,currentY,100,cellHeight*0.15));

    buttonGesture = new QPushButton(this);

    buttonGesture->setGeometry(QRect(0,0,cellWidth,cellHeight));
    buttonGesture->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    // connect(buttonGesture, SIGNAL(clicked()), this, SLOT(cellClicked()));
}

// SLOT
// void PostCell::cellClicked()
// {
//     qDebug("cellClicked");
//     qDebug() << (this->parent())->
// }

// CUSTOM
void PostCell::initPost(QString imageUrl,QString title,QString contents,QString date,QString comment,QString profile,QString nick,QString like)
{
    this->imageLabel->setText(imageUrl);
    this->titleLabel->setText(title);
    this->contentsLabel->setText(contents);
    this->dateLabel->setText(date);
    this->commentLabel->setText(comment);
    this->profileLabel->setText(profile);
    this->nickLabel->setText(nick);
    this->likeLabel->setText(like);
}
