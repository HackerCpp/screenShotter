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

void Panel::setObgectName(){
   slyderColor->setObjectName("sliderColor");
   up->setObjectName("UpWidget");
   down->setObjectName("DownWidget");
   leftBtnsWidg->setObjectName("LeftBtns");
   rBtnW->setObjectName("RightBtns");
   deleteBtn->setObjectName("hideFigure");
   bringbackBtn->setObjectName("showFigure");
   btn->data()[0]->setObjectName("btnCursor");
   btn->data()[1]->setObjectName("btnPen");
   btn->data()[2]->setObjectName("btnBrush");
   btn->data()[3]->setObjectName("btnLine");
   btn->data()[4]->setObjectName("btnArrow");
   btn->data()[5]->setObjectName("btnEllipse");
   btn->data()[6]->setObjectName("btnRect");
   btn->data()[7]->setObjectName("btnNumb");
   btn->data()[8]->setObjectName("btnSep");
   btn->data()[9]->setObjectName("btnCitr");
   btn->data()[10]->setObjectName("btnText");
   btnEnter->setObjectName("btnEnter");
   btnMenu->setObjectName("btnMenu");
}

Panel::Panel(QWidget *parent) : QWidget(parent){
    m_size = QApplication::screens().at(0)->geometry();
    thisWidth = m_size.width()/2;
    thisHeight = m_size.height()/8;
    slyderColor = new QSlider(Qt::Horizontal);
    slyderColor->setMaximum(35);
    slyderThickness = new QSlider(Qt::Horizontal);
    slyderThickness->setMaximum(255);
    slydersLayout = new QHBoxLayout();
    this->deleteBtn = new QPushButton();
    this->bringbackBtn = new QPushButton();
    deleteBtn->setFixedSize(thisWidth/18,thisHeight/2 - thisHeight/20);
    bringbackBtn->setFixedSize(thisWidth/18,thisHeight/2 - thisHeight/20);
    slydersLayout->addWidget(deleteBtn);
    slydersLayout->addWidget(bringbackBtn);
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

    rBtnW->setFixedSize(thisWidth/18+thisWidth/25,thisHeight/2);
    this->setLayout(vBoxLayout);
    btnEnter->setFixedSize(thisWidth/14,thisHeight/2);
    btnMenu->setFixedSize(thisWidth/35,thisHeight/2);

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
    connect(this->deleteBtn, SIGNAL(clicked()), this, SIGNAL(hideLastFigure()));
    connect(this->bringbackBtn, SIGNAL(clicked()), this, SIGNAL(showLastFigure()));
    connect(this->slyderColor,SIGNAL(valueChanged(int)),this,SIGNAL(changeColor(int)));
    connect(this->slyderThickness,SIGNAL(valueChanged(int)),this,SIGNAL(changeWidthLine(int)));
    showDown = false;
    showHideDown();
    active=false;
    controlPosition();
}

void Panel::showHideDown(){
    QPropertyAnimation *animation = new QPropertyAnimation(down, "geometry");
    if(showDown){
        this->leftBtn->setIcon(QIcon("pict/openD.ico"));
        animation->setDuration(1000);
        animation->setStartValue(QRect(0, thisHeight - thisHeight/2, down->width(), down->width()));
        animation->setEndValue(QRect(0, 10, down->width(), down->height()));
        animation->start();
        showDown = false;
    }
    else{
        this->leftBtn->setIcon(QIcon("pict/closeU.ico"));
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
void Panel::controlPosition(){
    if(this->pos().x() < 0)
        this->move(0,this->pos().y());
    if(this->pos().y() < 0)
        this->move(this->pos().x(),0);
    if((this->pos().x()+width())> m_size.width())
        this->move(m_size.width()-width(),this->pos().y());
    if(this->pos().y() + (height()/2) > m_size.height())
        this->move(this->pos().x(),m_size.height()-(height()/2));
}
void Panel::mouseMoveEvent(QMouseEvent *event){
    if(active){
            QPoint d = previousPoint - event->globalPos();
            this->move(this->pos() - d);
            controlPosition();
    }
    this->previousPoint = event->globalPos();
}
void Panel::mouseReleaseEvent(QMouseEvent *event){
    active = false;
}
