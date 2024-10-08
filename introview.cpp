#include "introview.h"
#include "mainwindow.h"

IntroView::IntroView(QWidget *parent)
    : QWidget{parent}
{
    writeBtn = util.makePushButton(this, "write", "", 8, false, "");
    int btnHeight = 30;
    int writeBtnY = parent->height() - (((MainWindow *) (this->parent()))->toolbarHeight)
                    - btnHeight;
    writeBtn->setGeometry(QRect(0, writeBtnY, ((parent->width())*0.7) , 30));
    connect(writeBtn, SIGNAL(clicked()), this, SLOT(startWrite()));

    refreshBtn = util.makePushButton(this, "refresh", "", 8, false, "");
    refreshBtn->setGeometry(QRect(writeBtn->x()+writeBtn->width(), writeBtn->y(), ((parent->width())*0.3) , 30));
    connect(refreshBtn, SIGNAL(clicked()), this, SLOT(startRefresh()));
}

// SLOT
void IntroView::startWrite()
{
    qDebug("startWrite");
}

void IntroView::startRefresh()
{
    qDebug("startRefresh");
}

// CUSTOM
void IntroView::initIntro()
{
    qDebug("initIntro");
}
