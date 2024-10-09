#ifndef POSTCELL_H
#define POSTCELL_H

#include <QWidget>
#include <QLabel>

class PostCell : public QWidget
{
    Q_OBJECT
private:
    QLabel* imageLabel;
    QLabel* titleLabel;
    QLabel* contentsLabel;
    QLabel* dateLabel;
    QLabel* commentLabel;
    QLabel* profileLabel;
    QLabel* nickLabel;
    QLabel* likeLabel;

public:
    explicit PostCell(QWidget *parent = nullptr);
    void initPost(QString imageUrl="",QString title="",QString contents="",QString date="",QString comment="",QString profile="",QString nick="",QString like="");

signals:
};

#endif // POSTCELL_H
