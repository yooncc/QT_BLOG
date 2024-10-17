#ifndef WRITEVIEW_H
#define WRITEVIEW_H

#include <QWidget>
// #include <QScrollArea>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "util.h"
#include "client.h"

class WriteView : public QWidget
{
    Q_OBJECT
private:
    // QScrollArea* scrollArea;
    QPushButton* backBtn;
    QPushButton* writeBtn;
    QLineEdit *titleEdit;
    QTextEdit *contentEdit;
public:
    explicit WriteView(QWidget *parent = nullptr);
    Util util;
public slots:
    void backAct();
    void writeAct();

signals:
};

#endif // WRITEVIEW_H
