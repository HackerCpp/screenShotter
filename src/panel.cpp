#include "inc/panel.h"
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
#include <QMessageBox>
#include <QSizePolicy>
#include <QSize>
#include "inc/panel/btninsert.h"
#include <QDebug>




void Panel::setObgectName(){
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
   checkBox->setObjectName("checkBox");
   m_how->setObjectName("how");
}
void Panel::setActiveRemoveBtn(bool isActive){
    if(isActive)
       deleteBtn->setIcon(QIcon(":/res/pict/remove_y.png"));
    else
       deleteBtn->setIcon(QIcon(":/res/pict/remove_n.png"));
}
void Panel::setActiveInsertBtn(bool isActive){
    if(isActive)
       bringbackBtn->setIcon(QIcon(":/res/pict/insert_y.png"));
    else
       bringbackBtn->setIcon(QIcon(":/res/pict/insert_n.png"));
}
Panel::Panel(QWidget *parent) : QWidget(parent){
    m_settings = new QSettings;
    m_size = QApplication::screens().at(0)->geometry();
    thisWidth = m_size.width()/2;
    thisHeight = 110;// m_size.height()/8;
    m_btnWidth = thisWidth/16;
    m_howWidth = m_btnWidth/2 + m_btnWidth/5;
    m_btnEnterWidth = m_btnWidth*2 - m_btnWidth/2 - m_btnWidth/6;
    heightCheckBox = 20;
    slyderColor = new SliderColor();
    slyderThickness = new SliderSize();
    slyderThickness->setFixedWidth(m_btnWidth*2 + m_btnWidth/2);
    slydersLayout = new QHBoxLayout();
    deleteBtn = new BtnInsert();
    bringbackBtn = new BtnInsert();

    m_toolBarTwoo = new QToolBar();
    m_toolBarTwoo->addWidget(deleteBtn);
    m_toolBarTwoo->addSeparator();
    m_toolBarTwoo->addWidget(bringbackBtn);
    m_toolBarTwoo->setFixedHeight(30);
    bringbackBtn->setIcon(QIcon(":/res/pict/insert_n.png"));
    deleteBtn->setIcon(QIcon(":/res/pict/remove_n.png"));
    deleteBtn->setFixedSize(QSize(m_btnWidth,30));
    bringbackBtn->setFixedSize(QSize(m_btnWidth,30));
    deleteBtn->setIconSize(deleteBtn->size()*4);// QSize(20,20));
    bringbackBtn->setIconSize(bringbackBtn->size()*4);

    m_toolBarTwoo->setStyleSheet("QToolBar{background: transparent;}\
QToolBar::Separator{width:1px;height:5px;background:#5a5a5a;}");
    deleteBtn->setStyleSheet("QPushButton{background: transparent;}");
    bringbackBtn->setStyleSheet("QPushButton{background: transparent;}");

    checkBox = new QCheckBox("Подложка");
    checkBox->setFixedSize(110,heightCheckBox+20);
    checkBox->setStyleSheet("QCheckBox{background-color: rgba(0, 0, 0, 0.8);\
color:white;border:0.5px solid grey;padding-left: 5px;}\
QCheckBox::indicator::unchecked{\
background-color: rgba(1, 1, 1, 1);\
border:8px solid white;}\
QCheckBox::indicator::checked{\
background-color: rgba(0, 0, 0, 0.4);\
border:1px solid white;border-radius:2px;}");
    slydersLayout->setMargin(0);
    slydersLayout->addWidget(m_toolBarTwoo);
    slydersLayout->addWidget(slyderColor);
    slydersLayout->addWidget(slyderThickness);
    slydersLayout->addSpacing(20);

    up = new QWidget();
    down= new QWidget();

    down->setLayout(slydersLayout);
    down->setStyleSheet("QWidget{background-color: rgba(0, 0, 0, 0.8);}");

    //this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

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
    btnMenu = new BtnMnu();
    btnEnter = new Btn();
    btnEnter->setIcon(QIcon(":/res/pict/ok.png"));

    rBtnW->setLayout(rBtnL);
    rBtnL->setMargin(0);
    rBtnL->addWidget(btnEnter);
    rBtnL->addWidget(btnMenu);
    btnEnter->setFixedSize(m_btnEnterWidth * 0.8,thisHeight/2);
    btnMenu->setFixedSize(m_btnEnterWidth * 0.2,thisHeight/2);
    leftWidg = new QWidget();
    leftWidg->setFixedSize(m_howWidth,height());//за что перетаскивать

    leftLayout = new QVBoxLayout();
    leftLayout->setMargin(0);
    leftBtn = new QPushButton();
    //leftBtn->setFixedSize(thisHeight/5,thisHeight/5);//открытие панели
    leftWidg->setLayout(leftLayout);
    m_how = new QWidget();

    leftLayout->addWidget(m_how);
    //leftLayout->addWidget(leftBtn);//Добавление открытия панели

    this->toolBar = new QToolBar();
    toolBar->addWidget(leftWidg);
    //this->toolBar->addSeparator();
    btn = new QVector<BtnToolTip *>(11);
    toolBar->setStyleSheet("QToolBar::Separator{width:1px;background:#e9e9e9;}\
QToolBar{background:#f5f5f5;spacing:0}");
    int index = 0;
    for(auto  b = btn->begin();b < btn->end();b++){
        this->toolBar->addSeparator();
        *b = new BtnToolTip(index);
        ++index;
        BtnToolTip * btnInd = reinterpret_cast<BtnToolTip*>(*b);
        connect(btnInd,&BtnToolTip::showToolTipP,this,&Panel::showToolTipP);
        connect(btnInd,&BtnToolTip::hideToolTipP,this,&Panel::hideToolTipP);
        this->toolBar->addWidget(*b);
        btnInd->setCheckable(true);
        btnInd->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
        btnInd->setFixedWidth(m_btnWidth);
        btnInd->setMinimumHeight(thisHeight/2);
    }
    btn->data()[0]->setIcon(QIcon(":/res/pict/arr.png"));
    btn->data()[1]->setIcon(QIcon(":/res/pict/pen.png"));
    btn->data()[2]->setIcon(QIcon(":/res/pict/brush.png"));
    btn->data()[3]->setIcon(QIcon(":/res/pict/line.png"));
    btn->data()[4]->setIcon(QIcon(":/res/pict/arrow.png"));
    btn->data()[5]->setIcon(QIcon(":/res/pict/text.png"));
    btn->data()[6]->setIcon(QIcon(":/res/pict/ell.png"));
    btn->data()[7]->setIcon(QIcon(":/res/pict/rect.png"));
    btn->data()[8]->setIcon(QIcon(":/res/pict/num.png"));
    btn->data()[9]->setIcon(QIcon(":/res/pict/sep.png"));
    btn->data()[10]->setIcon(QIcon(":/res/pict/cit.png"));
    for(int i = 0; i < 11;i++){
        btn->data()[i]->setIconSize(btn->data()[i]->size());
    }
    int btnS = m_settings->value("/Settings/Panel/Btn").toInt();
    prevBtnInd = btn->at(btnS);
    btn->at(btnS)->setChecked(true);//******************************
    leftBtnsLayuot->addWidget(toolBar);
    //leftBtnsWidg->setFixedSize(thisWidth -  thisWidth/5,thisHeight/2);
    down->setFixedSize((m_btnWidth + 1)*btn->size(),thisHeight/2);
    rBtnW->setFixedSize(m_btnEnterWidth,thisHeight/2 - 3);
    this->setLayout(vBoxLayout);

    m_menu = new ContextMenu;
    btnMenu->setMenu(m_menu);

    hBoxLayout->addWidget(leftBtnsWidg);//Верхние кнопки
    hBoxLayout->addStretch(10);//промежуток
    hBoxLayout->addWidget(rBtnW);//верхняя кнопка сохранить ресунок
    hBoxLayout->setMargin(0);
    up->setLayout(hBoxLayout);
    //up->setFixedSize(thisWidth,thisHeight/2);
    vBoxLayout->setMargin(0);
    vBoxLayout->addWidget(down,1,0);
    vBoxLayout->addWidget(up,0,0);
    vBoxLayout->addWidget(checkBox,2,0);

    //setAttribute( Qt::WA_TranslucentBackground, true );
    setFixedSize(((m_btnWidth + 1) * btn->size()) + m_howWidth + m_btnEnterWidth + 20,thisHeight);
    //setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    setObgectName();
    connect(this->leftBtn, SIGNAL(clicked()), this, SLOT(showHideDown()));
    foreach(QPushButton* btnInd,*this->btn){
       connect(btnInd, SIGNAL(clicked()), this, SLOT(checkBtns()));
    }
    showOnlySlyders();
    connect(this->btnEnter, SIGNAL(clicked()), this, SLOT(checkBtnsOk()));
    connect(this->btnEnter, SIGNAL(clicked()), this, SIGNAL(enterBtn()));
    connect(this->deleteBtn, SIGNAL(clicked()), this, SIGNAL(hideLastFigure()));
    connect(this->bringbackBtn, SIGNAL(clicked()), this, SIGNAL(showLastFigure()));
    connect(this->slyderColor,SIGNAL(cahngeColor(QColor)),this,SIGNAL(changeColor(QColor)));
    connect(this->slyderThickness,SIGNAL(valueChanged(int)),this,SIGNAL(changeWidthLine(int)));
    connect(m_menu,&ContextMenu::save,this,&Panel::savePicture);
    connect(m_menu,&ContextMenu::copy,this,&Panel::copy);
    connect(m_menu,&ContextMenu::global,this,&Panel::checkBtnsOk);
    connect(m_menu,&ContextMenu::global,this,&Panel::enterBtn);
    connect(checkBox,&QCheckBox::stateChanged,this,&Panel::checkBoxClicked);
    connect(btnEnter,SIGNAL(rightClick()),btnMenu,SLOT(showMenuT()));
    //showDown = false;
    //showHideDown();
    //active=false;
    controlPosition();
}
void Panel::setWidth(int width){
    slyderThickness->setValue(width);
    emit changeWidthLine(width);
}
void Panel::checkBoxPosition(){
    checkBox->move(m_howWidth,thisHeight);
}
void Panel::setcheckBox(bool isChecked){
    checkBox->setChecked(isChecked);
}
void Panel::showOll(){
    slyderColor->show();
    checkBox->show();

    this->setFixedHeight(thisHeight + checkBox->height() + 8);
    down->move(m_howWidth,thisHeight - thisHeight/2 - 10);
    checkBoxPosition();
}
void Panel::showOnlySlyders(){
    slyderColor->show();
    checkBox->hide();
    this->setFixedHeight(thisHeight);
    down->move(m_howWidth,thisHeight - thisHeight/2 - 10);
}
void Panel::changeFigure(int fig){
    if(fig == 0)
        Panel::showOll();
    else if(fig == 1)
        showOnlySlyders();
    else if(fig == 2)
        showOnlyOneSlyder();
}
void Panel::showOnlyOneSlyder(){
    slyderColor->hide();
    checkBox->hide();
    this->setFixedHeight(thisHeight);
    down->move(m_howWidth,thisHeight - thisHeight/2 - 10);
}
void Panel::showHideDown(){
    QPropertyAnimation *animation = new QPropertyAnimation(down, "geometry");
    if(showDown){
        this->leftBtn->setIcon(QIcon("pict/openD.png"));
        this->leftBtn->setIconSize(QSize(leftBtn->width(),leftBtn->height()));
        animation->setDuration(300);
        animation->setStartValue(QRect(m_howWidth, thisHeight - thisHeight/2 - 10, down->width(), down->width()));
        animation->setEndValue(QRect(m_howWidth, 2, down->width(), down->height()));
        animation->start();
        showDown = false;
    }
    else{
        this->leftBtn->setIcon(QIcon("pict/closeD.png"));
        this->leftBtn->setIconSize(QSize(leftBtn->width(),leftBtn->height()));
        animation->setDuration(300);
        animation->setStartValue(QRect(m_howWidth, 2, down->width(), down->height()));
        animation->setEndValue(QRect(m_howWidth, thisHeight - thisHeight/2 - 10, down->width(), down->width()));
        animation->start();
        showDown = true;
    }
}
void Panel::checkBtns(){
    int quant = 0;
    foreach(BtnToolTip* btnInd,*btn){
        if(btnInd->isChecked())
            ++quant;
    }
    if(quant > 1){
        prevBtnInd->setChecked(false);
        foreach(BtnToolTip* btnInd,*btn){
            if(btnInd->isChecked()){
                prevBtnInd = btnInd;
                break;
            }
        }
    }
    else if(quant < 1){
        prevBtnInd->setChecked(true);
    }
    if(prevBtnInd->isChecked()){
        if(btn->indexOf(dynamic_cast<BtnToolTip*>(prevBtnInd)) == 5)
            showOll();
        else if(btn->indexOf(prevBtnInd) == 9 || btn->indexOf(prevBtnInd) == 10)
            showOnlyOneSlyder();
        else{
            showOnlySlyders();
        }
        emit changeBtn(btn->indexOf(prevBtnInd)+1);
    }
    else {
        emit changeBtn(1);
    }
}
Panel::~Panel(){
    m_settings->setValue(("/Settings/Panel/Btn"), btn->indexOf(prevBtnInd) == 0?1:btn->indexOf(prevBtnInd));
    if(m_settings){
        delete m_settings;
        m_settings = nullptr;
    }
}

void Panel::checkBtnsOk(){
    this->hide();
}
void Panel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        if(event->globalX() > this->pos().x() & event->globalX() < this->pos().x()+40){
        active = true;
        this->previousPoint = event->globalPos();
        this->setCursor(Qt::ClosedHandCursor);
        }
    }
}
void Panel::mouseDoubleClickEvent(QMouseEvent *event){
    this->setCursor(Qt::ClosedHandCursor);
}
void Panel::controlPosition(){
    if(this->pos().x() < 0)
        this->move(0,this->pos().y());
    if(this->pos().y() < 0)
        this->move(this->pos().x(),0);
    if((this->pos().x()+width())> m_size.width())
        this->move(m_size.width()-width(),this->pos().y());
    if(this->pos().y() + (height()) > m_size.height())
        this->move(this->pos().x(),m_size.height()-(height()));
}
void Panel::mouseMoveEvent(QMouseEvent *event){
    if(active){
            QPoint d = previousPoint - event->globalPos();
            this->move(this->pos() - d);
            controlPosition();
    }
    this->previousPoint = event->globalPos();
}
void Panel::showInPosition(int x,int y,int x2,int y2,int width,int height){
    QPropertyAnimation *animation = new QPropertyAnimation(down, "geometry");
    animation->setDuration(50);
    animation->setStartValue(QRect(m_howWidth , 2, down->width(), down->height()));
    animation->setEndValue(QRect(m_howWidth, thisHeight - thisHeight/2 - 10, down->width(), down->height()));
    animation->start();

    if(y > height - this->height() - 20){
        if(y2 > this->height())
            this->move(x2-this->width(),y2 - this->height());
        else
            this->move(width,height);
    }
    else{
        this->move(x-this->width(),y+20);
    }
    Panel::controlPosition();
    this->show();
}
void Panel::changePosition(int x,int y,int x2,int y2,int width,int height){
    if(y > height - this->height()-20){
        if(y2 > this->height())
            this->move(x2-this->width(),y2 - this->height());
        else
            this->move(width,height);
    }
    else{
        this->move(x-this->width(),y+20);
    }
    Panel::controlPosition();
}
void Panel::mouseReleaseEvent(QMouseEvent *event){
    this->setCursor(Qt::ArrowCursor);
    active = false;
}
