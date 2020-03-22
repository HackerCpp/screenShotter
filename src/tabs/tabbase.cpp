#include "inc/tabs/tabbase.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScreen>

void TabBase::setName(){
    this->setObjectName("BaseWind");
    headerLabelText->setObjectName("HeaderText");
    headerBtn->setObjectName("HeaderBtn");
    headerLabelIcon->setObjectName("HeaderIcon");
    m_WidgetHeader->setObjectName("HeaderWidget");
}


TabBase::TabBase(){
    m_size = QApplication::screens().at(0)->geometry();
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    mainVBoxLayout = new QVBoxLayout;
    mainVBoxLayout->setMargin(0);
    mainVBoxLayout->setSpacing(0);
    headerLayout = new QHBoxLayout;
    m_WidgetHeader = new QWidget;
    m_WidgetHeader->setLayout(headerLayout);
    headerLabelIcon = new QLabel();

    headerLabelText = new QLabel();
    headerBtn = new QPushButton;
    headerLayout->addWidget(headerLabelIcon);
    headerLayout->addWidget(headerLabelText);
    headerLayout->addWidget(headerBtn);
    this->setLayout(mainVBoxLayout);
    mainVBoxLayout->addWidget(m_WidgetHeader);
    headerBtn->setFixedSize(60,30);

    connect(headerBtn, SIGNAL(clicked()), this, SLOT(hideWin()));
    setName();
}
TabBase::~TabBase(){
    this->deleteLater();
}
void TabBase::hideWin(){
    this->hide();
}
void TabBase::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        m_active = true;
        this->m_previousPoint = event->globalPos();
    }
}
void TabBase::controlPosition(){
    if(this->pos().x() < 0)
        this->move(0,this->pos().y());
    if(this->pos().y() < 0)
        this->move(this->pos().x(),0);
    if((this->pos().x()+width())> m_size.width())
        this->move(m_size.width()-width(),this->pos().y());
    if(this->pos().y() + (height()/2) > m_size.height())
        this->move(this->pos().x(),m_size.height()-(height()/2));
}
void TabBase::mouseMoveEvent(QMouseEvent *event){
    if(m_active){
            QPoint d = m_previousPoint - event->globalPos();
            this->move(this->pos() - d);
            controlPosition();
    }
    this->m_previousPoint = event->globalPos();
}
void TabBase::mouseReleaseEvent(QMouseEvent *event){
    m_active = false;
}
