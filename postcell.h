#ifndef POSTCELL_H
#define POSTCELL_H

#include <QLabel>
#include <QTextEdit>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>
#include <QPainterPath>

class PostCell : public QWidget
{
    Q_OBJECT
private:
    QLabel *imageLabel;
    QLabel *titleLabel;
    // QLabel *contentsLabel;
    QTextEdit *contentsLabel;
    QLabel *dateLabel;
    QLabel *commentLabel;
    QLabel *profileLabel;
    QLabel *nickLabel;
    QLabel *likeLabel;
    int row;
    int col;

public:
    explicit PostCell(int row, int col, QWidget *parent = nullptr);
    void initPost(QString imageUrl = "",
                  QString title = "",
                  QString contents = "",
                  QString date = "",
                  QString comment = "",
                  QString profile = "",
                  QString nick = "",
                  QString like = "");
    QPushButton *buttonGesture;
protected:
    void enterEvent(QEnterEvent *event) override {
        QWidget::enterEvent(event); // 기본 동작 호출
        // qDebug() << "Mouse entered cell at row:" << row << "col:" << col;
    }

    void leaveEvent(QEvent *event) override {
        QWidget::leaveEvent(event); // 기본 동작 호출
        // qDebug() << "Mouse left cell at row:" << row << "col:" << col;
    }
public slots:
    // void cellClicked();
signals:
};

#endif // POSTCELL_H
