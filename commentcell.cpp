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


void CommentCell::initComment(comment cmt, Post_info* post) {
    this->nickLabel->setText(cmt.nick);
    this->contentsLabel->setText(cmt.contents);
    this->curCmt = cmt;
    this->curPost = post;

    if (cmt.nick == client.cliInfo.MemberNickName) {
        modBtn = util.makePushButton(this, "수정", "", 8, false, "");
        modBtn->setGeometry((QRect(this->width()-(8+64), 4, 30, 20)));
        connect(modBtn, SIGNAL(clicked()), this, SLOT(modAct()));

        delBtn = util.makePushButton(this, "삭제", "", 8, false, "");
        delBtn->setGeometry((QRect(modBtn->x()+modBtn->width()+4, 4, 30, 20)));
        connect(delBtn, SIGNAL(clicked()), this, SLOT(delAct()));

    }
}

void CommentCell::modAct() {
    qDebug() << "mod1";
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
        QString contents = contentsField->text(); // 여기에 실제 id 값을 넣으세요

        if (contents == "") {
            util.showErrorMsg(this, "수정할 댓글을 입력하세요!");
            return;
        }

        emit modSignal(this->curCmt.idx, contents);  // 신호 발생
    });
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    dialog.exec();
    // client.modifyComment(this->curPost,this->curCmt);
}

void CommentCell::delAct() {
    client.deleteComment(this->curPost,this->curCmt);
    emit delSignal(this->curCmt.idx);  // 신호 발생
}
