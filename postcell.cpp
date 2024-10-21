#include "postcell.h"

PostCell::PostCell(QWidget *parent)
    : QWidget{parent}
{
    int cellWidth = 260, cellHeight = 300, currentY = 0;

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(QRect(0, 0, cellWidth, cellHeight));
    backgroundLabel->setStyleSheet("background-color: white; border-radius: 7px;");

    imageLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    contentsLabel = new QTextEdit(this);
    dateLabel = new QLabel(this);
    commentLabel = new QLabel(this);
    profileLabel = new QLabel(this);
    nickLabel = new QLabel(this);
    likeLabel = new QLabel(this);

    imageLabel->setGeometry(QRect(0, currentY, cellWidth, cellHeight * 0.35));
    imageLabel->setStyleSheet("background-color: lightgray; color: red;");
    currentY += imageLabel->height();

    titleLabel->setGeometry(QRect(0, currentY, cellWidth, cellHeight * 0.1));
    titleLabel->setStyleSheet("color: black; font-weight: bold; font-size: 16px;");
    titleLabel->setAlignment(Qt::AlignCenter); // 텍스트 가운데 정렬
    currentY += titleLabel->height();

    contentsLabel->setGeometry(QRect(8, currentY, cellWidth - 16, cellHeight * 0.3));
    contentsLabel->setStyleSheet("color: black; font-size: 12px; border: none;");

    currentY += contentsLabel->height();

    QLabel *border1 = new QLabel(this);
    border1->setGeometry(QRect(0, currentY, cellWidth, 1));
    border1->setStyleSheet("background-color: lightgray;");

    dateLabel->setGeometry(QRect(8, currentY, cellWidth / 2 , cellHeight * 0.1));
    dateLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    commentLabel->setGeometry(
        QRect(cellWidth / 2, currentY, cellWidth / 2 - 8, cellHeight * 0.1));
    commentLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    currentY += dateLabel->height();

    QLabel *border2 = new QLabel(this);
    border2->setGeometry(QRect(0, currentY, cellWidth, 1));
    border2->setStyleSheet("background-color: lightgray;");

    profileLabel->setGeometry(QRect(8, currentY, cellHeight * 0.15, cellHeight * 0.15));
    // profileLabel->setStyleSheet("border: 1px solid black;");

    nickLabel->setGeometry(QRect(profileLabel->x() + profileLabel->width() + 4,
                                 currentY,
                                 cellWidth / 3,
                                 cellHeight * 0.15));
    nickLabel->setStyleSheet("color: black; font-weight: bold; font-size: 13px;");

    likeLabel->setGeometry(QRect(cellWidth - 100, currentY, 100, cellHeight * 0.15));

    buttonGesture = new QPushButton(this);

    buttonGesture->setGeometry(QRect(0, 0, cellWidth, cellHeight));
    buttonGesture->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    // connect(buttonGesture, SIGNAL(clicked()), this, SLOT(cellClicked()));
}

// SLOT
// void PostCell::cellClicked()
// {
//     qDebug("cellClicked");
//     // qDebug() << (this->parent())->
// }

// CUSTOM
void PostCell::initPost(QString imageUrl,
                        QString title,
                        QString contents,
                        QString date,
                        QString comment,
                        QString profile,
                        QString nick,
                        QString like)
{
    this->imageLabel->setText(imageUrl);
    this->titleLabel->setText(title);
    this->contentsLabel->setText(contents);
    // contentsLabel->setWordWrap(true);
    // contentsLabel->adjustSize();
    this->dateLabel->setText(date);

    QString cmtStr = "댓글 ";
    cmtStr.append(comment);
    this->commentLabel->setText(cmtStr);

    // this->profileLabel->setText(profile);
    QPixmap pixmap(profile);
    if (pixmap.isNull()) {
        pixmap = QPixmap(":/lion.jpg");
    }
    profileLabel->setPixmap(pixmap.scaled(profileLabel->size(), Qt::KeepAspectRatio));

    this->nickLabel->setText(nick);
    // this->likeLabel->setText(like);
}
