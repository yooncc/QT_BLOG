#ifndef POSTVIEW_H
#define POSTVIEW_H

#include <QPushButton>
#include <QScrollArea>
#include <QTextEdit>
#include <QWidget>
#include <QGridLayout>
#include "client.h"
#include "util.h"
#include "post_info.h"
#include "commentcell.h"

class PostView : public QWidget
{
    Q_OBJECT
private:
    QScrollArea *scrollArea;
    QPushButton *backBtn;
    QPushButton *delBtn;
    QPushButton *modBtn;
    QLabel *titleLabel;
    QLabel *nickLabel;
    QLabel *dateLabel;
    QLabel *imageLabel;
    QLabel *contentsLabel;
    QWidget *scrollWidget;
    QTextEdit *commentEdit;
    QPushButton *cmtBtn;
    QGridLayout *commentGridLayout;
    int postId;
    int viewOriginX;
    int index;

public:
    explicit PostView(QWidget *parent = nullptr);
    void postviewInit(
        QString title, QString nick, QString date, QString image, QString contents, int id, int index);
    void commentRenew();
    Util util;

public slots:
    void backAct();
    void cmtAct();
    void modAct();
    void delAct();
    void cmtModAct(int index, QString mContents);
    void cmtDelAct(int index);
    // void Download();
signals:
};

#endif // POSTVIEW_H
