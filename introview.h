#ifndef INTROVIEW_H
#define INTROVIEW_H

#include <QWidget>
#include "util.h"

class IntroView : public QWidget
{
    Q_OBJECT
private:
    QPushButton *writeBtn;
    QPushButton *refreshBtn;
public:
    explicit IntroView(QWidget *parent = nullptr);
    void initIntro();
    Util util;
public slots:
    void startWrite();
signals:
};

#endif // INTROVIEW_H
