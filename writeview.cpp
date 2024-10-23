#include "writeview.h"

WriteView::WriteView(QWidget *parent)
    : QWidget{parent}
{
    int screenHeight = parent->height() - (((MainWindow *) (this->parent()))->toolbarHeight);
    int viewOriginX = (parent->width() / 7) * 2;

    QWidget *writePlace = new QWidget(this);
    writePlace->setGeometry(
        QRect(viewOriginX, 0, parent->width() - (viewOriginX * 2), screenHeight));
    writePlace->setStyleSheet("background-color: lightgray;");

    titleEdit = new QLineEdit(writePlace);
    titleEdit->setPlaceholderText("제목을 입력하세요.");
    titleEdit->setGeometry(QRect(8, 50, writePlace->width() - 16, 50));
    connect(titleEdit, SIGNAL(textChanged()), this, SLOT(titleCheckTextLimit()));
    titleEdit->setStyleSheet(
        "background-color: white; color: black;font-size: 25px; font-weight: bold;");

    contentEdit = new QTextEdit(writePlace);
    contentEdit->setPlaceholderText("내용을 입력하세요.");
    contentEdit->setGeometry(QRect(8, 120, writePlace->width() - 16, screenHeight - 120 - 120));
    connect(contentEdit, SIGNAL(textChanged()), this, SLOT(contentsCheckTextLimit()));
    contentEdit->setStyleSheet(
        "background-color: white; color: black;font-size: 16px; font-weight: bold;");

    writeBtn = util.makePushButton(writePlace, "완료", "", 8, false, "");
    writeBtn->setGeometry(
        (QRect(8, contentEdit->y() + contentEdit->height() + 16, writePlace->width() - 16, 100)));
    connect(writeBtn, SIGNAL(clicked()), this, SLOT(writeAct()));

    backBtn = util.makePushButton(this, "back", "", 8, false, "");
    backBtn->setGeometry((QRect(50, 50, 50, 50)));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backAct()));

    fileBtn = util.makePushButton(this, "file", "", 8, false, "");
    fileBtn->setGeometry((QRect(writePlace->x()+writePlace->width()+50, 50, 50, 50)));
    connect(fileBtn, SIGNAL(clicked()), this, SLOT(fileAct()));

    imageBtn = util.makePushButton(this, "image", "", 8, false, "");
    imageBtn->setGeometry((QRect(writePlace->x()+writePlace->width()+50, 116, 50, 50)));
    connect(imageBtn, SIGNAL(clicked()), this, SLOT(imageAct()));
}

void WriteView::setModify(QString title, QString contents)
{
    qDebug("setModify");
    this->titleEdit->setText(title);
    this->contentEdit->setText(contents);
}


void WriteView::backAct()
{
    qDebug("backAct");
    ((MainWindow *) (this->parent()))->initMain();
}

void WriteView::fileAct()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*);;Text Files (*.txt);;Images (*.png *.jpg)"));
    if (fileName.isEmpty())
        return;
    QFileInfo fileInfo(fileName);
    client.fn = fileInfo.fileName();
}

void WriteView::imageAct()
{
    qDebug("imageAct");
}

void WriteView::writeAct()
{
    qDebug("writeAct");

    if (titleEdit->text() == "" || contentEdit->toPlainText().isEmpty()) {
        util.showErrorMsg(this, "모든 항목을 채워주세요!");
        return;
    }
    if (this->index == -1) {
        client.writePost(titleEdit->text(), contentEdit->toPlainText());
        client.uploadFile(client.fn);

        ((MainWindow *) (this->parent()))->initMain();
    }
    else {
        client.postInfos[index]->title = titleEdit->text();
        client.postInfos[index]->contents = contentEdit->toPlainText();
        client.modifyPost(client.postInfos[index]);
        ((MainWindow *) (this->parent()))->goToPost(index,1);
    }
}

void  WriteView::titleCheckTextLimit()
{
    QString currentText = titleEdit->text();

    // 글자 수가 100자를 넘으면 텍스트를 잘라냄
    if (currentText.length() > 100) {
        // 처음 100글자만 유지
        titleEdit->setText(currentText.left(100));
    }
}

void  WriteView::contentsCheckTextLimit()
{
    QString currentText = contentEdit->toPlainText();

    // 글자 수가 100자를 넘으면 텍스트를 잘라냄
    if (currentText.length() > 100) {
        // 커서 위치 저장
        QTextCursor cursor = contentEdit->textCursor();
        // 처음 100글자만 유지
        contentEdit->setPlainText(currentText.left(100));
        // 커서 위치 복원
        contentEdit->setTextCursor(cursor);
    }
}
