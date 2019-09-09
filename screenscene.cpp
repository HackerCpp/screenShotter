#include "screenscene.h"
#include <QGuiApplication>
#include <QCursor>
#include <QPixmap>
#include <QGraphicsLineItem>

ScreenScene::ScreenScene(){
    close = 0;
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);
    QCursor * cursor = new QCursor(QPixmap("cursors\\PF3C_zlk_Cross"));

    QGraphicsPixmapItem *pixIteam = this->addPixmap(pixmap);
    rectCentr = this->addRect(QRect(0,0,this->width(),this->height()),
                                                     QPen(QColor(0,0,0,50)),QBrush(QColor(0,0,0,50)));
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
    if (event->buttons() == Qt::LeftButton){
        this->left_mouse = true;
        if(!close){
            close = 1;
            this->rectCentr->setBrush(QBrush(QColor(0,0,0,0)));
            this->rectCentr->setRect(QRectF(event->scenePos().x(),event->scenePos().y(),0,0));
            this->rectIteam[0] = this->addRect(QRect(0,0,event->scenePos().x(),event->scenePos().y()),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
            this->rectIteam[1] = this->addRect(QRect(event->scenePos().x(),0,event->scenePos().x(),0),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
            this->rectIteam[2] = this->addRect(QRect(event->scenePos().x(),0,this->width() - event->scenePos().x(),this->height() -(this->height() - event->scenePos().y())),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
            this->rectIteam[3] = this->addRect(QRect(event->scenePos().x(),event->scenePos().y(),this->width() - event->scenePos().x(),0),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
            this->rectIteam[4] = this->addRect(QRect(event->scenePos().x(),event->scenePos().y(),this->width() - event->scenePos().x(),this->height() - event->scenePos().y()),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
            this->rectIteam[5] = this->addRect(QRect(event->scenePos().x(),event->scenePos().y(),0,this->height() - event->scenePos().y() ),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
            this->rectIteam[6] = this->addRect(QRect(0,event->scenePos().y(),event->scenePos().x(),this->height()-event->scenePos().y()),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
            this->rectIteam[7] = this->addRect(QRect(0,event->scenePos().y(),event->scenePos().x(),0),
                                               QPen(QColor(Qt::white)),QBrush(QColor(0,0,0,50)));
        }

    }


    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
}

void ScreenScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close != 2){
        this->verticalLine->setLine(QLineF(event->scenePos().x(),0,event->scenePos().x(),this->height()));
        this->horizontalLine->setLine(QLineF(0,event->scenePos().y(),this->width(),event->scenePos().y()));
    }
     if (close == 1 && left_mouse == true){
        if(previousPoint.x() < event->scenePos().x() & previousPoint.y() < event->scenePos().y())
            this->rectCentr->setRect(QRectF().adjusted(previousPoint.x(),previousPoint.y(), event->scenePos().x(), event->scenePos().y()));
        else if (previousPoint.x() > event->scenePos().x() & previousPoint.y() > event->scenePos().y())
            this->rectCentr->setRect(QRectF().adjusted(event->scenePos().x(), event->scenePos().y(),previousPoint.x(),previousPoint.y()));
        else if(previousPoint.x() < event->scenePos().x() & previousPoint.y() > event->scenePos().y())
            this->rectCentr->setRect(QRectF().adjusted(previousPoint.x(),event->scenePos().y(), event->scenePos().x(),previousPoint.y() ));
        else if (previousPoint.x() > event->scenePos().x() & previousPoint.y() < event->scenePos().y())
            this->rectCentr->setRect(QRectF().adjusted(event->scenePos().x(),previousPoint.y(),previousPoint.x(),event->scenePos().y()));
        this->rectIteam[0]->setRect(QRectF().adjusted(0,0,rectCentr->rect().x(),rectCentr->rect().y()));
        this->rectIteam[1]->setRect(QRectF().adjusted(rectCentr->rect().x(),0,rectCentr->rect().width()+rectCentr->rect().x(),rectCentr->rect().y()));
        this->rectIteam[2]->setRect(QRectF().adjusted(rectCentr->rect().x() + rectCentr->rect().width(),0,this->width(),rectCentr->rect().y()));
        this->rectIteam[3]->setRect(QRectF().adjusted(rectCentr->rect().x() + rectCentr->rect().width(),rectCentr->rect().y(),this->width(),rectCentr->rect().y() + rectCentr->rect().height()));
        this->rectIteam[4]->setRect(QRectF().adjusted(rectCentr->rect().x() + rectCentr->rect().width(),rectCentr->rect().y() + rectCentr->rect().height(),this->width(),this->height()));
        this->rectIteam[5]->setRect(QRectF().adjusted(rectCentr->rect().x(),rectCentr->rect().y() + rectCentr->rect().height(),rectCentr->rect().x() + rectCentr->rect().width(),this->height()));
        this->rectIteam[6]->setRect(QRectF().adjusted(0,rectCentr->rect().y() + rectCentr->rect().height(),rectCentr->rect().x(),this->height()));
        this->rectIteam[7]->setRect(QRectF().adjusted(0,rectCentr->rect().y(),rectCentr->rect().x(),rectCentr->rect().y() + rectCentr->rect().height()));
     }
    // Отрисовываем линии с использованием предыдущей координаты

    // Обновляем данные о предыдущей координате
    //previousPoint = event->scenePos();
}
void ScreenScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if (this->left_mouse){
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
    }

}
