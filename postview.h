#ifndef POSTVIEW_H
#define POSTVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include "util.h"

class PostView : public QWidget
{
    Q_OBJECT
private:
    QScrollArea* scrollArea;
    QPushButton* backBtn;
public:
    explicit PostView(QWidget *parent = nullptr);
    Util util;

public slots:
    void backAct();
signals:
};

#endif // POSTVIEW_H
