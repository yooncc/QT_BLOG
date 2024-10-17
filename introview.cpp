#include "introview.h"
#include "client.h"

// extern Client *client;

IntroView::IntroView(QWidget *parent)
    : QWidget{parent}
{

    int btnHeight = 30;
    int writeBtnY = parent->height() - (((MainWindow *) (this->parent()))->toolbarHeight)
                    - btnHeight;

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // 스크롤 영역이 동적으로 크기 조정 가능하게 설정
    scrollArea->setGeometry(QRect(0,0,parent->width(),writeBtnY));

    QWidget* scrollWidget = new QWidget;
    postGridLayout = new QGridLayout(scrollWidget);
    postGridLayout->setContentsMargins(16, 16, 16, 16);

    scrollArea->setWidget(scrollWidget);

    writeBtn = util.makePushButton(this, "write", "", 8, false, "");

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
    // initIntro();
}

void IntroView::startRefresh()
{
    qDebug("startRefresh");
    client.setFlag(3);
    client.sendMessage("3:1");
    // 기존 위젯 모두 제거
    QLayoutItem *child;
    while ((child = postGridLayout->takeAt(0)) != nullptr) {
        delete child->widget();  // 레이아웃에서 위젯을 제거하고 삭제
        delete child;  // 레이아웃 아이템 삭제
    }
}

void IntroView::cellClicked()
{
    qDebug("cellClicked");
    ((MainWindow*)(this->parent()))->goToPost();
}

// CUSTOM
void IntroView::initIntro()
{
    qDebug("initIntro");
    qDebug() << client.postInfos.size();
    // 기존 위젯 모두 제거
    QLayoutItem *child;
    while ((child = postGridLayout->takeAt(0)) != nullptr) {
        delete child->widget();  // 레이아웃에서 위젯을 제거하고 삭제
        delete child;  // 레이아웃 아이템 삭제
    }

    int n,m=-1;
    for (int i=0; i<client.postInfos.size();i++) {
        n = i%4;
        if (i%4==0)
            m++;
        PostCell* postCell = new PostCell;
        postCell->setFixedSize(260,300);

        postCell->initPost("image1",client.postInfos[i]->title,client.postInfos[i]->contents,"2024/10/9","12","profile",client.postInfos[i]->nick,"99");
        postGridLayout->addWidget(postCell,m,n);
    }



}
