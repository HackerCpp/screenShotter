#include "inc/tabs/btnsforurl.h"
#include <QDesktopServices>
#include <QClipboard>
#include <QApplication>
#include <QFile>
#include <QUrl>
#include <QTextStream>
#include <QPropertyAnimation>
#include <QFileInfo>

QUrl getUrl(){
    QFile in( "platforms/QURL.dll" );
    QUrl url;
    if( in.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &in );
        url = stream.readAll().remove("\\");
        in.close();
    }
    return url;
}
bool BtnsForUrl::isFileExist(){
    QFileInfo check_file("platforms/QURL.dll");
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
BtnsForUrl::BtnsForUrl(int widthParent,int heightParent,QWidget* parent):
m_width(widthParent),m_height(heightParent){
    this->setParent(parent);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
    m_hBoxLayout = new QHBoxLayout;
    m_timer = new QTimer();
    for(int i = 0; i < 2;i++){
        m_pushBtn[i] = new QPushButton;
        m_pushBtn[i]->setFixedSize(m_width/3,m_height/5);
        m_pushBtn[i]->setObjectName("enter" + QString::number(i+4));
    }
    this->setLayout(m_hBoxLayout);
    m_hBoxLayout->addWidget(m_pushBtn[0]);
    m_hBoxLayout->addWidget(m_pushBtn[1]);
    connect(m_pushBtn[0],&QPushButton::clicked,this,&BtnsForUrl::openUrl);
    connect(m_pushBtn[1],&QPushButton::clicked,this,&BtnsForUrl::copyUrl);   
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    if(isFileExist())
        this->show();
    else
        this->hide();

}
void BtnsForUrl::updateTimer(){
    this->hide();
    m_timer->stop();
}
void BtnsForUrl::showVawe(){
    this->show();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(8000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    m_timer->start(7000);
}
void BtnsForUrl::enterEvent(QEvent *event){
    if(this->parent() != nullptr)
        return;
    m_timer->stop();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0.9);
    animation->setEndValue(1);
    animation->start();
}
void BtnsForUrl::leaveEvent(QEvent *event){
    if(this->parent() != nullptr)
        return;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(8000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    m_timer->start(7000);
}
void BtnsForUrl::openUrl(){
    QDesktopServices::openUrl(getUrl());
}
void BtnsForUrl::copyUrl(){
    QUrl url = getUrl();
    QString stringUrl =  url.toEncoded();
    QApplication::clipboard()->setText(stringUrl);
}
