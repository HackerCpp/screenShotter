#include "inc/tabs/tray.h"
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>


Tray::Tray(QIcon icon):QSystemTrayIcon(icon){
    //this->setVisible(true);
    connect(this,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(mouseclick(QSystemTrayIcon::ActivationReason)));
    connect(this,SIGNAL(messageClicked()),this,SLOT(messageClick()));
    //connect(m_menu,SIGNAL(aboutToShow()),this,SLOT(messageClick()));
    //connect(m_menu,SIGNAL(aboutToHide()),this,SLOT(addMenu()));
}
void Tray::mouseclick(QSystemTrayIcon::ActivationReason reas){
    //qDebug() << reas;
    if(reas == ActivationReason::Context)
        emit rightMouseClick();
    else if(reas == ActivationReason::Trigger)
        emit leftMouseClick();
}
void Tray::addMenu(){
    /*m_menu = new QMenu();
    m_menu->addAction( new QAction(tr(""), this));
    m_menu->setAttribute(Qt::WA_TranslucentBackground);
    m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint);
    //m_menu->setStyleSheet("background-color: rgba(0, 0, 0, 0.2);color:#000000;");
    this->setContextMenu(m_menu);
    connect(m_menu,SIGNAL(aboutToShow()),this,SLOT(messageClick()));*/
}
void Tray::messageClick(){
    //qDebug() << "messageClick";
}
bool Tray::event(QEvent *event){
    //qDebug() << event;
    return true;
}
