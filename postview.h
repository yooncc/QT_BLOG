#ifndef POSTVIEW_H
#define POSTVIEW_H

#include <QButtonGroup>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QStandardPaths>
#include <QTextEdit>
#include <QWidget>
#include "client.h"
#include "commentcell.h"
#include "post_info.h"
#include "util.h"

class PostView : public QWidget
{
    Q_OBJECT
private:
    QScrollArea *scrollArea;
    QPushButton *backBtn;
    QPushButton *delBtn;
    QPushButton *modBtn;
    QPushButton *downloadBtn;
    QComboBox *comboBox;
    QLabel *titleLabel;
    QLabel *nickLabel;
    QLabel *dateLabel;
    QLabel *imageLabel;
    QLabel *contentsLabel;
    QLabel *filesLabel;
    QWidget *scrollWidget;
    QTextEdit *commentEdit;
    QPushButton *cmtBtn;
    QGridLayout *commentGridLayout;
    int postId;
    int viewOriginX;
    int index;
    int myint;

public:
    explicit PostView(QWidget *parent = nullptr);
    void postviewInit(QString title,
                      QString nick,
                      QString date,
                      QString image,
                      QString contents,
                      int id,
                      int index);
    void commentRenew();
    Util util;

public slots:
    void backAct();
    void cmtAct();
    void modAct();
    void delAct();
    void cmtModAct(int index);
    void cmtDelAct(int index);
    void downloadFile();
signals:
};

#endif // POSTVIEW_H
