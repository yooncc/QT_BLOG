#include "introview.h"
#include "mainwindow.h"

IntroView::IntroView(QWidget *parent)
    : QWidget{parent}
{

    writeBtn = util.makePushButton(this, "write", "", 8, false, "");
    int btnHeight = 30;
    int writeBtnY =  parent->height()-(((MainWindow *)(this->parent()))->toolbarHeight)-btnHeight;
    writeBtn->setGeometry(QRect(0,writeBtnY,parent->width(),30));
    connect(writeBtn, SIGNAL(clicked()), this, SLOT(startWrite()));
}

// SLOT
void IntroView::startWrite()
{
    qDebug("startWrite");

}

// CUSTOM
void IntroView::initIntro()
{
    qDebug("initIntro");

}
