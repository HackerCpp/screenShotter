#include "screenscene.h"
#include <QGuiApplication>
#include <QCursor>
#include <QPixmap>
#include <QGraphicsLineItem>
#include <curtain.h>
#include <QGraphicsView>

ScreenScene::ScreenScene(){
    close = 0;
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);
    QCursor * cursor = new QCursor(QPixmap("cursors\\PF3C_zlk_Cross"));

    QGraphicsPixmapItem *pixIteam = this->addPixmap(pixmap);
    rectCentr = new Curtain(0,0,this->width(),this->height());
    this->addItem(rectCentr);

    horizontalLine = this->addLine(QLineF(0,this->height()/2,this->width(),this->height()/2),
                                                    QPen(Qt::white));
    verticalLine = this->addLine(QLineF(this->width()/2,0,this->width()/2,this->height()),
                                                    QPen(Qt::white));
    horizontalLine->setCursor(*cursor);
    panel = new Panel();
    panel->hide();
}
void ScreenScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    verticalLine->hide();
    horizontalLine->hide();
    QGraphicsScene::mousePressEvent(event);

}

void ScreenScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

   if(close != 2){
        this->verticalLine->setLine(QLineF(event->scenePos().x(),0,event->scenePos().x(),this->height()));
        this->horizontalLine->setLine(QLineF(0,event->scenePos().y(),this->width(),event->scenePos().y()));
    }
   QGraphicsScene::mouseMoveEvent(event);
}
void ScreenScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    /*if (this->left_mouse){
        this->left_mouse = false;
        if(close == 1){
            rectIteam[0]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_3")));
            rectIteam[1]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_1")));
            rectIteam[2]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_4")));
            rectIteam[3]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_2")));
            rectIteam[4]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_3")));
            rectIteam[5]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_1")));
            rectIteam[6]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_4")));
            rectIteam[7]->setCursor(QCursor(QPixmap("cursors\\PF3C_zlk_size_2")));
            panel->setGeometry(event->scenePos().x() - panel->width(),event->scenePos().y() + 30,panel->width(),panel->height());
            panel->show();
            close = 2;
        }
    }*/

}

