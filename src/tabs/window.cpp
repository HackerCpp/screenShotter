#include "inc/tabs/window.h"
#include <QApplication>
#include <QPropertyAnimation>
#include <QRect>
#include <QScreen>

void Wind::setObgectName(){
    groupBoxUp->setObjectName("grBoxUp");
    groupBoxAver->setObjectName("grBoxAv");

}

Wind::Wind(){
    trayIcon = new QSystemTrayIcon(QIcon("pict\\aver.ico"));
    trayIcon->show();
    QRect size = QApplication::screens().at(0)->geometry();

    int thisWidth = size.width()/8;
    int thisHeight = size.height()/2 - size.height()/10;
    for(int i = 0; i < 6; i++){
        pushBtn[i] = new QPushButton;
        pushBtn[i]->setFixedSize(thisWidth/3,thisHeight/5);
        pushBtn[i]->setObjectName("enter" + QString::number(i));
    }
    gridLayoutUp = new QGridLayout;
    hBoxLayoutAver = new QHBoxLayout;
    hBoxLayoutDown = new QHBoxLayout;
    groupBoxUp = new QGroupBox;
    groupBoxAver = new QGroupBox;
    downWidg = new QWidget;
    labelleft = new QLabel("<a href='https://kwork.ru'>помощь</a>");
    labelRight = new QLabel("<a href='https://kwork.ru'>выход</a>");
    labelRight->setOpenExternalLinks(false);
    labelleft->setOpenExternalLinks(false);
    labelRight->setTextInteractionFlags( Qt::LinksAccessibleByMouse);

    mainVBoxLayout->addWidget(groupBoxUp);
    mainVBoxLayout->addWidget(groupBoxAver);
    mainVBoxLayout->addWidget(downWidg);
    groupBoxUp->setLayout(gridLayoutUp);
    groupBoxAver->setLayout(hBoxLayoutAver);
    downWidg->setLayout(hBoxLayoutDown);
    gridLayoutUp->addWidget(pushBtn[0],0,1);
    gridLayoutUp->addWidget(pushBtn[1],0,2);
    gridLayoutUp->addWidget(pushBtn[2],1,1);
    gridLayoutUp->addWidget(pushBtn[3],1,2);
    hBoxLayoutAver->addWidget(pushBtn[4]);
    hBoxLayoutAver->addWidget(pushBtn[5]);
    hBoxLayoutDown->addStretch(20);
    hBoxLayoutDown->addWidget(labelleft);
    hBoxLayoutDown->addWidget(labelRight);
    hBoxLayoutDown->addStretch(20);
    labelleft->setOpenExternalLinks(true);
    this->setFixedSize(thisWidth,thisHeight);
    this->move(size.width()-thisWidth-40 ,size.height() - thisHeight-100);
    headerLabelIcon->setPixmap(QPixmap("pict\\aver.ico"));//.scaled(30,30));

    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(showWin()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showWin()));
    connect(labelRight,SIGNAL(linkActivated(const QString&)),this,SLOT(destroy()));
    connect(pushBtn[0],&QPushButton::clicked,this,&Wind::enterPartOfScreen);
    connect(pushBtn[1],&QPushButton::clicked,this,&Wind::enterFullScrin);
    connect(pushBtn[2],&QPushButton::clicked,this,&Wind::enterHistory);
    connect(pushBtn[3],&QPushButton::clicked,this,&Wind::enterSettings);
    connect(pushBtn[4],&QPushButton::clicked,this,&Wind::enterOpen);
    connect(pushBtn[5],&QPushButton::clicked,this,&Wind::enterCopy);
    this->hide();
}
void Wind::hideWin(){
    this->hide();
}
void Wind::showWin(){
    if(this->isVisible())
        return;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(this->pos().x(), this->pos().y() + this->height(), this->width(), this->width()));
    animation->setEndValue(QRect(this->pos().x(), this->pos().y(), this->width(), this->height()));
    animation->start();
    this->show();
}
void Wind::destroy(){
    this->deleteLater();
}
Wind::~Wind(){
    this->trayIcon->hide();
    delete this->trayIcon;
    this->deleteLater();
    qApp->quit();
}
