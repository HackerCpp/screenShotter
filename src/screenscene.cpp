#include "inc\screenscene.h"
#include <QGuiApplication>
#include <QCursor>
#include <QPixmap>
#include <QGraphicsLineItem>
#include "inc\figure\curtain.h"
#include "inc\figure\penandbrush.h"
#include "inc\figure\arrow.h"
#include "inc\figure\line.h"
#include "inc\figure\ellips.h"
#include <QGraphicsView>
#include <QString>
#include <QDebug>
#include <QGraphicsProxyWidget>

void ScreenScene::newFigure(QGraphicsSceneMouseEvent *event){
    Figure *v = nullptr;
    switch (figure) {
    case 1:{
        if(curentFigure)
            curentFigure->setActive(false);

        this->curentFigure = dynamic_cast<Figure*>(itemAt(event->scenePos(),QTransform()));
        if(curentFigure){
            curentFigure->setActive(true);
        }
        update();
        QGraphicsScene::mousePressEvent(event);
        break;
    }
    case 2:{
        v = new PenAndBrush(event->scenePos().x(),event->scenePos().y(),m_pen,true);
        break;
    }
    case 3:{
        v = new PenAndBrush(event->scenePos().x(),event->scenePos().y(),m_pen,false);
        break;
    }
    case 4:{
        v = new Line(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 5:{
        v = new Arrow(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 6:{
        v = new Ellips(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 7:{
        v = new Curtain(event->scenePos().x(),event->scenePos().y(),1,1,m_pen,0);
        break;
    }
    case 8:{
        v = new Curtain(event->scenePos().x(),event->scenePos().y(),1,1,m_pen,numberSquare++);
        break;
    }
    case 9:{
        //v = new Curtain(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 10:{
        //v = new Curtain(event->scenePos().x(),event->scenePos().y(),1,1,m_pen,0);
        break;
    }
    default:
        break;
    }

    if(v){
        curentFigure = v;
        addItem(v);
        v->show();
        QGraphicsScene::mousePressEvent(event);
        this->left_mouse = true;
    }
    update();
}
void ScreenScene::mouseClkClose(QGraphicsSceneMouseEvent *event){
    verticalLine->hide();
    horizontalLine->hide();
    rectCentr->hide();
    close = 1;
    lUp = lDown = rUp = rDown = event->scenePos();
    QPointF point = rDown - lUp;
    QPen pen(Qt::white);
    pen.setWidthF(0.25);
    QBrush brush(QColor(0,0,0,150));
    textItem = addSimpleText("");

    rectIteam[0] = addRect(QRect().adjusted(0,0,lUp.x(),lUp.y()),pen,brush);
    rectIteam[1] = addRect(QRect().adjusted(lUp.x(),0,rUp.x(),rUp.y()),pen,brush);
    rectIteam[2] = addRect(QRect().adjusted(rUp.x(),0,width(),rUp.y()),pen,brush);
    rectIteam[3] = addRect(QRect().adjusted(rUp.x(),rUp.y(),width(),rDown.y()),pen,brush);
    rectIteam[4] = addRect(QRect().adjusted(rDown.x(),rDown.y(),width(),height()),pen,brush);
    rectIteam[5] = addRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),height()),pen,brush);
    rectIteam[6] = addRect(QRect().adjusted(0,lDown.y(),lDown.x(),height()),pen,brush);
    rectIteam[7] = addRect(QRect().adjusted(0,lUp.y(),lDown.x(),lDown.y()),pen,brush);
    for(int i = 0;i<8;i++){
        rectIteam[i]->setZValue(10);
    }
    beginPoint = event->scenePos();
    this->left_mouse = true;
}
void ScreenScene::mouseClkOpen(QGraphicsSceneMouseEvent *event){
    isCitrain = false;
    for(int i = 0;i<8;i++){
        if(itemAt(event->scenePos(),QTransform()) == rectIteam[i]){
            isCitrain = true;
            break;
        }
    }
    if(!isCitrain){
        newFigure(event);
        return;
    }
    prevPoint = event->scenePos();
    this->left_mouse = true;
    textItem->show();
}
void ScreenScene::mouseMoveBegin(QGraphicsSceneMouseEvent *event){
    this->verticalLine->setLine(QLineF(event->scenePos().x(),0,event->scenePos().x(),this->height()));
    this->horizontalLine->setLine(QLineF(0,event->scenePos().y(),this->width(),event->scenePos().y()));
}
void ScreenScene::mouseMoveClose(QGraphicsSceneMouseEvent *event){
    textItem->show();
     if(event->scenePos().x() > beginPoint.x() & event->scenePos().y() > beginPoint.y()){
         lDown.setY(event->scenePos().y());
         rUp.setX(event->scenePos().x());
         rDown = event->scenePos();
     }
     else if(event->scenePos().x() < beginPoint.x() & event->scenePos().y() < beginPoint.y()){
         rUp.setY(event->scenePos().y());
         lDown.setX(event->scenePos().x());
         lUp = event->scenePos();
     }
     else if(event->scenePos().x() < beginPoint.x() & event->scenePos().y() > beginPoint.y()){
         rDown.setY(event->scenePos().y());
         lUp.setX(event->scenePos().x());
         lDown = event->scenePos();
     }
     else if(event->scenePos().x() > beginPoint.x() & event->scenePos().y() < beginPoint.y()){
         lUp.setY(event->scenePos().y());
         rDown.setX(event->scenePos().x());
         rUp = event->scenePos();
     }
     rectIteam[0]->setRect(QRect().adjusted(0,0,lUp.x(),lUp.y()));
     rectIteam[1]->setRect(QRect().adjusted(lUp.x(),0,rUp.x(),rUp.y()));
     rectIteam[2]->setRect(QRect().adjusted(rUp.x(),0,width(),rUp.y()));
     rectIteam[3]->setRect(QRect().adjusted(rUp.x(),rUp.y(),width(),rDown.y()));
     rectIteam[4]->setRect(QRect().adjusted(rDown.x(),rDown.y(),width(),height()));
     rectIteam[5]->setRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),height()));
     rectIteam[6]->setRect(QRect().adjusted(0,lDown.y(),lDown.x(),height()));
     rectIteam[7]->setRect(QRect().adjusted(0,lUp.y(),lDown.x(),lDown.y()));
     textItem->setPos(rDown.x()+10,rDown.y()-30);
     textItem->setText(QString::number(rUp.x() - lUp.x()) + "x" + QString::number(rDown.y() - rUp.y()));
}
void ScreenScene::mouseMoveOpen(QGraphicsSceneMouseEvent *event){
    if(!isCitrain){
        QGraphicsScene::mouseMoveEvent(event);
        update();
        return;
    }
     QPointF p = prevPoint - event->scenePos();
     if(prevPoint.x() < lUp.x()){
         lUp.setX(lUp.x()-p.x());
         lDown.setX(lDown.x()-p.x());
     }
     if(prevPoint.x() > rUp.x()){
         rUp.setX(rUp.x()-p.x());
         rDown.setX(rDown.x()-p.x());
     }
     if(prevPoint.y() > rDown.y()){
         rDown.setY(rDown.y()-p.y());
         lDown.setY(lDown.y()-p.y());
     }
     if(prevPoint.y() < rUp.y()){
         rUp.setY(rUp.y()-p.y());
         lUp.setY(lUp.y()-p.y());
     }
     if(lUp.x() >= rUp.x()){
         lUp.setX(rUp.x());
         rDown.setX(lDown.x());
         lDown.setX(lUp.x());
         rUp.setX(rDown.x());
     }
     if(lUp.y() >= lDown.y()){
         lUp.setY(lDown.y());
         rDown.setY(rUp.y());
         lDown.setY(rDown.y());
         rUp.setY(lUp.y());
     }
     rectIteam[0]->setRect(QRect().adjusted(0,0,lUp.x(),lUp.y()));
     rectIteam[1]->setRect(QRect().adjusted(lUp.x(),0,rUp.x(),rUp.y()));
     rectIteam[2]->setRect(QRect().adjusted(rUp.x(),0,width(),rUp.y()));
     rectIteam[3]->setRect(QRect().adjusted(rUp.x(),rUp.y(),width(),rDown.y()));
     rectIteam[4]->setRect(QRect().adjusted(rDown.x(),rDown.y(),width(),height()));
     rectIteam[5]->setRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),height()));
     rectIteam[6]->setRect(QRect().adjusted(0,lDown.y(),lDown.x(),height()));
     rectIteam[7]->setRect(QRect().adjusted(0,lUp.y(),lDown.x(),lDown.y()));
     textItem->setPos(rDown.x()+10,rDown.y()-30);
     textItem->setText(QString::number(rUp.x() - lUp.x()) + "x" + QString::number(rDown.y() - rUp.y()));
     prevPoint = event->scenePos();
     update();
}
void ScreenScene::mouseRelClose(QGraphicsSceneMouseEvent *event){
    rectIteam[0]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_3")));
    rectIteam[1]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_1")));
    rectIteam[2]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_4")));
    rectIteam[3]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_2")));
    rectIteam[4]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_3")));
    rectIteam[5]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_1")));
    rectIteam[6]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_4")));
    rectIteam[7]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_2")));
    panel->setGeometry(event->scenePos().x() - panel->width(),event->scenePos().y() + 30,panel->width(),panel->height());
    //panelItem->setPos(event->scenePos().x() - panel->width(),event->scenePos().y() + 30);
    panel->show();
    close = 2;
}

ScreenScene::ScreenScene(){
    numberSquare = 1;
    curentFigure = nullptr;
    figure = 0;
    close = 0;
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);
    QCursor * cursor = new QCursor(QPixmap("cursors\\PF3C_zlk_Cross"));
    QGraphicsPixmapItem *pixIteam = this->addPixmap(pixmap);
    rectCentr = addRect(QRect(0,0,width(),height()),QPen(QColor(0,0,0,150)),QBrush(QColor(0,0,0,150)));
    QPen pen(Qt::white);
    pen.setWidthF(0.25);
    horizontalLine = this->addLine(QLineF(0,this->height()/2,this->width(),this->height()/2),pen);
    verticalLine = this->addLine(QLineF(this->width()/2,0,this->width()/2,this->height()),pen);
    horizontalLine->setCursor(*cursor);
    panel = new Panel();
    connect(this->panel,SIGNAL(changeColor(int)),this,SLOT(changeColor(int)));
    connect(this->panel,SIGNAL(changeWidthLine(int)),this,SLOT(changeWLine(int)));
    connect(this->panel,SIGNAL(changeBtn(int)),this,SLOT(changefigure(int)));
}
void ScreenScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!close){
       mouseClkClose(event);
    }
    if(close == 1){
        prevPoint = event->scenePos();
        this->left_mouse = true;
        textItem->show();
    }
    if(close == 2){
        mouseClkOpen(event);
    }
}

void ScreenScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
   if(!close){
        mouseMoveBegin(event);
    }
   else if(close == 1){
       if(left_mouse){
           mouseMoveClose(event);
       }
   }
   else if (close == 2){
       if(left_mouse){
           mouseMoveOpen(event);
        }
   }
}
void ScreenScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if (this->left_mouse){
        this->left_mouse = false;
        textItem->hide();
        if(close == 1){
            mouseRelClose(event);
        }
        else if(close == 2){

        }
        QGraphicsScene::mouseReleaseEvent(event);
    }
}
void ScreenScene::changeColor(int index){
    if(index < 20 & index > -1)
        this->m_pen.setColor(tableColor[index]);
    if(curentFigure)
        curentFigure->setColor(m_pen.color());
    update();
}
void ScreenScene::changeWLine(int index){
    this->m_pen.setWidthF(index/10);
    if(curentFigure)
        curentFigure->setWidthLine(index/10);
    update();
}
ScreenScene::~ScreenScene(){
    delete this->panel;
    this->deleteLater();
}
