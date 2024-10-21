#ifndef POSTVIEW_H
#define POSTVIEW_H

#include <QPushButton>
#include <QScrollArea>
#include <QTextEdit>
#include <QWidget>
#include <QGridLayout>
#include "client.h"
#include "util.h"
#include "commentcell.h"

class PostView : public QWidget
{
    Q_OBJECT
private:
    QScrollArea *scrollArea;
    QPushButton *backBtn;
    QLabel *titleLabel;
    QLabel *nickLabel;
    QLabel *dateLabel;
    QLabel *imageLabel;
    QTextEdit *contentsLabel;
    QWidget *scrollWidget;
    QTextEdit *commentEdit;
    QPushButton *cmtBtn;
    QGridLayout *commentGridLayout;
    int postId;
    int viewOriginX;

public:
    explicit PostView(QWidget *parent = nullptr);
    void postviewInit(
        QString title, QString nick, QString date, QString image, QString contents, int id);
    Util util;

public slots:
    void backAct();
    void cmtAct();
    // void Download();
signals:
};

#endif // POSTVIEW_H
