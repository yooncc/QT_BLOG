#ifndef INTROVIEW_H
#define INTROVIEW_H

#include <QGridLayout>
#include <QScrollArea>
#include <QWidget>
#include "client.h"
#include "mainwindow.h"
#include "postcell.h"
#include "util.h"

class IntroView : public QWidget
{
    Q_OBJECT
private:
    QPushButton *writeBtn;
    QPushButton *refreshBtn;
    PostCell *postCell;
    QScrollArea *scrollArea;
    QGridLayout *postGridLayout;

public:
    explicit IntroView(QWidget *parent = nullptr);
    void initIntro();
    Util util;
public slots:
    void setPost();
    void startWrite();
    void startRefresh();
    void cellClicked(int index);
signals:
};

#endif // INTROVIEW_H
