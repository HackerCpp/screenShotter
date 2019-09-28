#include "inc\panel.h"
#include <QFile>
#include <QToolButton>
#include <QStyleOptionSlider>
#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QPropertyAnimation>
#include <QDebug>
#include <QBitmap>
#include <QTime>
#include <QMouseEvent>


void Wind::setObgectName(){
    headerBtn->setObjectName("qwit");
    groupBoxUp->setObjectName("grBoxUp");
    groupBoxAver->setObjectName("grBoxAv");

}

Wind::Wind(){
    trayIcon = new QSystemTrayIcon(QIcon("pict\\aver.ico"));
    trayIcon->show();
    QRect size = QApplication::screens().at(0)->geometry();
    this->setWindowIcon(QIcon("pict\\aver.ico"));
    this->setWindowTitle("title");
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    int thisWidth = size.width()/8;
    int thisHeight = size.height()/2 - size.height()/10;
    for(int i = 0; i < 6; i++){
        pushBtn[i] = new QPushButton;
        pushBtn[i]->setFixedSize(thisWidth/3,thisHeight/5);
        pushBtn[i]->setObjectName("enter" + QString::number(i));
    }
    headerLayout = new QHBoxLayout;
    headerLabelIcon = new QLabel();
    headerLabelIcon->setPixmap(QPixmap("pict\\aver.ico").scaled(30,30));
    headerLabelText = new QLabel("Title");
    headerBtn = new QPushButton;
    headerBtn->setFixedSize(thisWidth/9,thisWidth/9);
    //headerBtn->setIcon(QPixmap("icon\\del.png"));
    headerLayout->addWidget(headerLabelIcon);
    headerLayout->addWidget(headerLabelText);
    headerLayout->addWidget(headerBtn);

    mainVBoxLayout = new QVBoxLayout;
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
    this->setLayout(mainVBoxLayout);
    mainVBoxLayout->addLayout(headerLayout);
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
    //gridLayoutUp->setMargin(0);
    //hBoxLayoutAver->setMargin(0);
    mainVBoxLayout->setMargin(4);
    this->setFixedSize(thisWidth,thisHeight);
    this->move(size.width()-thisWidth-40 ,size.height() - thisHeight-100);
    setObgectName();
    connect(headerBtn, SIGNAL(clicked()), this, SLOT(hideWin()));
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

void Panel::setObgectName(){
   slyderColor->setObjectName("sliderColor");
   up->setObjectName("UpWidget");
   down->setObjectName("DownWidget");
   leftBtnsWidg->setObjectName("LeftBtns");
   rBtnW->setObjectName("RightBtns");
}

Panel::Panel(QWidget *parent) : QWidget(parent){
    QRect size = QApplication::screens().at(0)->geometry();
    thisWidth = size.width()/2;
    thisHeight = size.height()/8;
    slyderColor = new QSlider(Qt::Horizontal);
    slyderColor->setMaximum(35);
    slyderThickness = new QSlider(Qt::Horizontal);
    slyderThickness->setMaximum(255);
    slydersLayout = new QHBoxLayout();
    slydersLayout->addWidget(slyderColor);
    slydersLayout->addSpacing(50);
    slydersLayout->addWidget(slyderThickness);

    up = new QWidget();
    down= new QWidget();
    down->setFixedSize(thisWidth -  thisWidth/5,thisHeight/2);
    down->setLayout(slydersLayout);

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    vBoxLayout = new QGridLayout;
    hBoxLayout = new QHBoxLayout;
    hBoxLayout->setContentsMargins(0,0,0,0);

    leftBtnsWidg = new QWidget();
    leftBtnsLayuot = new QHBoxLayout();
    leftBtnsLayuot->setMargin(0);
    leftBtnsWidg->setLayout(leftBtnsLayuot);

    rBtnW = new QWidget();
    rBtnL = new QHBoxLayout();
    rBtnL->setMargin(0);
    btnMenu = new QPushButton();
    btnEnter = new QPushButton();

    rBtnW->setLayout(rBtnL);
    rBtnL->addWidget(btnEnter);
    rBtnL->addWidget(btnMenu);

    leftWidg = new QWidget();
    leftWidg->setFixedSize(thisWidth/30,thisHeight/2 - thisHeight/10);
    leftLayout = new QVBoxLayout();
    leftLayout->setMargin(0);
    leftBtn = new QPushButton();
    leftBtn->setFixedSize(thisWidth/30,thisHeight/5);
    leftWidg->setLayout(leftLayout);
    leftLayout->addWidget(new QWidget());
    leftLayout->addWidget(leftBtn);

    this->toolBar = new QToolBar();
    toolBar->addWidget(leftWidg);
    this->toolBar->addSeparator();
    btn = new QVector<QPushButton *>(11);
    for(auto  b = btn->begin();b < btn->end();b++){
        *b = new QPushButton;
        QPushButton * btnInd = reinterpret_cast<QPushButton*>(*b);
        this->toolBar->addWidget(*b);
        btnInd->setCheckable(true);
        btnInd->setFixedSize(thisWidth/18,thisHeight/2 - thisHeight/20);
        this->toolBar->addSeparator();
    }
    prevBtnInd = btn->at(0);
    btn->at(0)->setChecked(true);
    this->toolBar->setFixedHeight(thisHeight/2);
    leftBtnsLayuot->addWidget(toolBar);
    leftBtnsWidg->setFixedSize(thisWidth -  thisWidth/5,thisHeight/2);

    rBtnW->setFixedSize(thisWidth/15+thisWidth/25,thisHeight/2);
    this->setLayout(vBoxLayout);
    btnEnter->setFixedSize(thisWidth/14,thisHeight/2);
    btnMenu->setFixedSize(thisWidth/25,thisHeight/2);

    hBoxLayout->addWidget(leftBtnsWidg);
    hBoxLayout->addStretch(50);
    hBoxLayout->addWidget(rBtnW);
    up->setLayout(hBoxLayout);
    up->setFixedSize(thisWidth,thisHeight/2);
    vBoxLayout->setMargin(0);
    vBoxLayout->addWidget(down,1,0);
    vBoxLayout->addWidget(up,0,0);

    setAttribute( Qt::WA_TranslucentBackground, true );
    setFixedSize(thisWidth,thisHeight);

    setObgectName();
    connect(this->leftBtn, SIGNAL(clicked()), this, SLOT(showHideDown()));
    foreach(QPushButton* btnInd,*this->btn){
       connect(btnInd, SIGNAL(clicked()), this, SLOT(checkBtns()));
    }
    connect(this->btnEnter, SIGNAL(clicked()), this, SLOT(checkBtnsOk()));
    connect(this->btnEnter, SIGNAL(clicked()), this, SIGNAL(enterBtn()));
    connect(this->slyderColor,SIGNAL(valueChanged(int)),this,SIGNAL(changeColor(int)));
    connect(this->slyderThickness,SIGNAL(valueChanged(int)),this,SIGNAL(changeWidthLine(int)));
    showDown = false;
    showHideDown();
    active=false;
}

void Panel::showHideDown(){
    QPropertyAnimation *animation = new QPropertyAnimation(down, "geometry");
    if(showDown){
        animation->setDuration(1000);
        animation->setStartValue(QRect(0, thisHeight - thisHeight/2, down->width(), down->width()));
        animation->setEndValue(QRect(0, 10, down->width(), down->height()));
        animation->start();
        showDown = false;
    }
    else{
        animation->setDuration(1000);
        animation->setStartValue(QRect(0, 10, down->width(), down->height()));
        animation->setEndValue(QRect(0, thisHeight - thisHeight/2, down->width(), down->width()));
        animation->start();
        showDown = true;
    }
}
void Panel::checkBtns(){
    if(prevBtnInd->isChecked())
        prevBtnInd->setChecked(false);
    foreach(QPushButton* btnInd,*this->btn){
        if(btnInd->isChecked()){
            prevBtnInd = btnInd;
        }
        else{
            btnInd->setChecked(false);
        }
    }
    if(prevBtnInd->isChecked())
        emit changeBtn(btn->indexOf(prevBtnInd)+1);
    else {
        emit changeBtn(1);
    }
}
void Panel::checkBtnsOk(){
    this->hide();
}
void Panel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        active = true;
        this->previousPoint = event->globalPos();
    }
}

void Panel::mouseMoveEvent(QMouseEvent *event){
    if(active){
            int dt = previousPoint.x() - event->globalX();
            QPoint d = previousPoint - event->globalPos();
            this->move(this->pos() - d);
    }
    this->previousPoint = event->globalPos();
}
void Panel::mouseReleaseEvent(QMouseEvent *event){
    active = false;
}
