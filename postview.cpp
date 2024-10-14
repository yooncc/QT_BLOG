#include "postview.h"
#include "mainwindow.h"

PostView::PostView(QWidget *parent)
    : QWidget{parent}
{
    int screenHeight = parent->height() - (((MainWindow *) (this->parent()))->toolbarHeight);
    int viewOriginX = (parent->width()/7) * 2;

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // 스크롤 영역이 동적으로 크기 조정 가능하게 설정
    scrollArea->setGeometry(QRect(viewOriginX,0,parent->width()-(viewOriginX*2),screenHeight));
    scrollArea->setStyleSheet("background-color: lightgray;");
    // QWidget* scrollWidget = new QWidget;
    // postGridLayout = new QGridLayout(scrollWidget);
    // postGridLayout->setContentsMargins(16, 16, 16, 16);

    backBtn = util.makePushButton(this, "back", "", 8, false, "");
    backBtn->setGeometry((QRect(50,50,50,50)));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backAct()));
}


void PostView::backAct()
{
    qDebug("backAct");
    ((MainWindow*)(this->parent()))->initMain();
}
