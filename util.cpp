#include "util.h"

Util::Util(QObject *parent)
    : QObject{parent}
{}

QAction *Util::makeAction(
    QString icon, QString text, QString shortCut, QString toolTip, QObject *recv, const char *slot)
{
    QAction *act = new QAction(text, this);
    if (icon.length())
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered(bool)), recv, slot);
    return act;
}

QPushButton *Util::makePushButton(QWidget *parent = nullptr,
                                  QString name = "",
                                  QString fontName = "",
                                  int fontSize = 12,
                                  bool isBold = false,
                                  QString icon = "")
{
    QPushButton *newPushBtn = new QPushButton(name, parent);
    // newPushBtn->setText(name);
    newPushBtn->setIcon(QIcon(icon));
    QFont font;
    font.setFamily(fontName);
    font.setPointSize(fontSize);
    font.setBold(isBold);
    newPushBtn->setFont(font);

    return newPushBtn;
}
