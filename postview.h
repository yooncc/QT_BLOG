#ifndef POSTVIEW_H
#define POSTVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QTextEdit>
#include "util.h"
#include "client.h"

class PostView : public QWidget
{
    Q_OBJECT
private:
    QScrollArea* scrollArea;
    QPushButton* backBtn;
    QLabel *titleLabel;
    QLabel *nickLabel;
    QLabel *dateLabel;
    QLabel *imageLabel;
    QLabel *contentsLabel;
    QWidget* scrollWidget;
    QTextEdit *commentEdit;
    QPushButton* cmtBtn;
    int postId;
    int viewOriginX;
public:
    explicit PostView(QWidget *parent = nullptr);
    void postviewInit(QString title, QString nick, QString date, QString image, QString contents, int id);
    Util util;

public slots:
    void backAct();
    void cmtAct();
signals:
};

#endif // POSTVIEW_H
