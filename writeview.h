#ifndef WRITEVIEW_H
#define WRITEVIEW_H

#include <QWidget>
// #include <QScrollArea>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include "client.h"
#include "util.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>


class WriteView : public QWidget
{
    Q_OBJECT
private:
    // QScrollArea* scrollArea;
    QPushButton *backBtn;
    QPushButton *fileBtn;
    QPushButton *imageBtn;
    QPushButton *writeBtn;
    QLineEdit *titleEdit;
    QTextEdit *contentEdit;

public:
    explicit WriteView(QWidget *parent = nullptr);
    Util util;
    void setModify(QString title, QString contents);
    int index;
public slots:
    void backAct();
    void fileAct();
    void imageAct();
    void writeAct();
    void titleCheckTextLimit();
    void contentsCheckTextLimit();

signals:
};

#endif // WRITEVIEW_H
