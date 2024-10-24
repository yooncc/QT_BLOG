#include "postcell.h"

PostCell::PostCell(int row, int col, QWidget *parent)
    : QWidget{parent}
{
    this->row = row; this->col = col;

    setMouseTracking(true); // 마우스 이벤트를 추적하도록 설정

    int cellWidth = 260, cellHeight = 300, currentY = 0;

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(QRect(0, 0, cellWidth, cellHeight));
    backgroundLabel->setStyleSheet("background-color: white; border-radius: 11px;");

    imageLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    contentsLabel = new QTextEdit(this);
    dateLabel = new QLabel(this);
    commentLabel = new QLabel(this);
    profileLabel = new QLabel(this);
    nickLabel = new QLabel(this);
    likeLabel = new QLabel(this);

    imageLabel->setGeometry(QRect(0, currentY, cellWidth, cellHeight * 0.35));

    currentY += imageLabel->height();

    titleLabel->setGeometry(QRect(8, currentY, cellWidth-16, cellHeight * 0.1));
    titleLabel->setStyleSheet("color: black; font-weight: bold; font-size: 16px;");
    titleLabel->setAlignment(Qt::AlignLeft); // 텍스트 가운데 정렬
    currentY += titleLabel->height();

    contentsLabel->setGeometry(QRect(8, currentY, cellWidth - 16, cellHeight * 0.3));
    // 수직 스크롤바 비활성화
    contentsLabel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

    profileLabel->setGeometry(QRect(8, currentY+cellHeight * 0.025, cellHeight * 0.1, cellHeight * 0.1));
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

    QPixmap pixmap(imageUrl);
    if (pixmap.isNull()) {
        pixmap = QPixmap(":/veda_w.png");
        imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatioByExpanding));
    }
    else {
        imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatioByExpanding));
        // imageLabel->setFixedSize(pixmap.size());
        QPainterPath path;
        QRectF rect = imageLabel->rect();
        path.addRoundedRect(rect, 11, 11);  // 전체 라운드 처리
        path.addRect(0, 11, rect.width(), rect.height() - 11); // 아래쪽은 평평하게

        // // 마스크 설정 (위젯의 클리핑 경계를 설정)
        QRegion maskRegion = QRegion(path.toFillPolygon().toPolygon());
        imageLabel->setMask(maskRegion);
    }

    this->titleLabel->setText(title);
    this->contentsLabel->setText(contents);
    // contentsLabel->setWordWrap(true);
    // contentsLabel->adjustSize();
    this->dateLabel->setText(date);

    QString cmtStr = "댓글 ";
    cmtStr.append(comment);
    this->commentLabel->setText(cmtStr);

    // this->profileLabel->setText(profile);
    pixmap = QPixmap(profile);
    if (pixmap.isNull()) {
        pixmap = QPixmap(":/profile.png");
    }
    profileLabel->setPixmap(pixmap.scaled(profileLabel->size(), Qt::KeepAspectRatio));

    this->nickLabel->setText(nick);
    // this->likeLabel->setText(like);



}
