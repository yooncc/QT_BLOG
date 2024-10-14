#include "introview.h"
#include "mainwindow.h"

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
    initIntro();
}

void IntroView::startRefresh()
{
    qDebug("startRefresh");
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
    // 기존 위젯 모두 제거
    QLayoutItem *child;
    while ((child = postGridLayout->takeAt(0)) != nullptr) {
        delete child->widget();  // 레이아웃에서 위젯을 제거하고 삭제
        delete child;  // 레이아웃 아이템 삭제
    }

    // for (int i=0; i<10; i++) {
    //     PostCell* postCell1 = new PostCell;
    //     postCell1->setFixedSize(260,300);
    //     postCell1->initPost("image1","title","contents","2024/10/9","12","profile","yooncc","99");
    //     postGridLayout->addWidget(postCell1,0,0);
    // }

    PostCell* postCell1 = new PostCell;
    postCell1->setFixedSize(260,300);
    postCell1->initPost("image1","title","contents","2024/10/9","12","profile","yooncc","99");
    connect(postCell1->buttonGesture, SIGNAL(clicked()), this, SLOT(cellClicked()));
    postGridLayout->addWidget(postCell1,0,0);

    PostCell* postCell2 = new PostCell;
    postCell2->setFixedSize(260,300);
    postCell2->initPost("image2","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell2,0,1);

    PostCell* postCell3 = new PostCell;
    postCell3->setFixedSize(260,300);
    postCell3->initPost("image3","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell3,0,2);

    PostCell* postCell4 = new PostCell;
    postCell4->setFixedSize(260,300);
    postCell4->initPost("image4","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell4,0,3);

    PostCell* postCell5 = new PostCell;
    postCell5->setFixedSize(260,300);
    postCell5->initPost("image5","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell5,1,0);

    PostCell* postCell6 = new PostCell;
    postCell6->setFixedSize(260,300);
    postCell6->initPost("image6","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell6,1,1);

    PostCell* postCell7 = new PostCell;
    postCell7->setFixedSize(260,300);
    postCell7->initPost("image7","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell7,1,2);

    PostCell* postCell8 = new PostCell;
    postCell8->setFixedSize(260,300);
    postCell8->initPost("image7","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell8,1,3);

    PostCell* postCell9 = new PostCell;
    postCell9->setFixedSize(260,300);
    postCell9->initPost("image7","title","contents","2024/10/9","12","profile","yooncc","99");
    postGridLayout->addWidget(postCell9,2,0);


}
