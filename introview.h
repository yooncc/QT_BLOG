#ifndef INTROVIEW_H
#define INTROVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include "util.h"
#include "postcell.h"

class IntroView : public QWidget
{
    Q_OBJECT
private:
    QPushButton *writeBtn;
    QPushButton *refreshBtn;
    PostCell *postCell;
    QScrollArea* scrollArea;
    QGridLayout *postGridLayout;

public:
    explicit IntroView(QWidget *parent = nullptr);
    void initIntro();
    Util util;
public slots:
    void startWrite();
    void startRefresh();
    void cellClicked();
signals:
};

#endif // INTROVIEW_H
