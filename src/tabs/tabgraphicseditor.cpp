#include "inc/tabs/tabgraphicseditor.h"


TabGraphicsEditor::TabGraphicsEditor(bool isFullScreen,QWidget *parent)
    : QGraphicsView(parent){
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
    m_scene = new ScreenScene(isFullScreen);
    this->setScene(m_scene);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->cursor().setPos(m_scene->width()/2,m_scene->height()/2);
    this->showFullScreen();
    connect(m_scene,SIGNAL(enterSavePixmap()),this,SIGNAL(enterSavePixmap()));
}

void TabGraphicsEditor::deleteCitrain(){
    delete this->m_scene;
    this->m_scene = nullptr;
    this->hide();
}

TabGraphicsEditor::~TabGraphicsEditor(){
    if(m_scene)
        delete m_scene;
    this->deleteLater();
}
