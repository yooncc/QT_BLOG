#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QAction>
#include <QPushButton>

class Util : public QObject
{
    Q_OBJECT
private:

public:
    explicit Util(QObject *parent = nullptr);
    QAction *makeAction(QString icon,
                        QString text,
                        QString shortCut,
                        QString toolTip,
                        QObject *recv,
                        const char *slot);
    QPushButton *makePushButton(
        QWidget *parent, QString name, QString fontName, int fontSize, bool isBold, QString icon);


signals:
};

#endif // UTIL_H
