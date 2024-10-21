#ifndef COMMENTCELL_H
#define COMMENTCELL_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QRect>

class CommentCell : public QWidget
{
    Q_OBJECT
public:
    explicit CommentCell(QWidget *parent = nullptr);
    QLabel* nickLabel;
    QTextEdit* contentsLabel;
    void initComment(QString nick, QString contents);

signals:
};

#endif // COMMENTCELL_H
