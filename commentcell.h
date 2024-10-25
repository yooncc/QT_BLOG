#ifndef COMMENTCELL_H
#define COMMENTCELL_H

#include <QLabel>
#include <QPushButton>
#include <QRect>
#include <QTextEdit>
#include <QWidget>
#include "client.h"
#include "post_info.h"
#include "util.h"

class CommentCell : public QWidget
{
    Q_OBJECT
private:
    Util util;
    comment curCmt;
    Post_info *curPost;

public:
    explicit CommentCell(QWidget *parent = nullptr);
    QLabel *nickLabel;
    QTextEdit *contentsLabel;
    void initComment(comment cmt, Post_info *post);
    QPushButton *modBtn;
    QPushButton *delBtn;

public slots:
    void modAct();
    void delAct();

signals:
    void delSignal(int index); // 신호 선언
    void modSignal(int index); // 신호 선언
};

#endif // COMMENTCELL_H
