#include "inc\figure\sepia.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QColor>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>

void Sepia::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}

Sepia::Sepia(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
    *this->pen = pen;
    this->brush->setColor(QColor(pen.color().red(),pen.color().green(),pen.color().blue(),pen.width() * 10));
    close = true;
    prevPoints = QPointF(x,y);
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
}
Q_GUI_EXPORT void qt_blurImage( QPainter* p, QImage& blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
void Sepia::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        if(isActive){

        }
        QImage img(m_w,m_h,QImage::Format_RGB32 );
        QPainter p( &img );
        //p.setRenderHint( QPainter::Antialiasing );
        scene()->render( painter, QRectF(), sceneBoundingRect() );
        p.end();
        painter->save();
        qt_blurImage(&p, img, 30, true, false );
        painter->drawImage(QRect(),img,QRect(m_x,m_y,m_w,m_h));
        //painter->drawRect(QRect(m_x,m_y,m_w,m_h));
        painter->restore();


        /*painter->setPen(*pen);
        this->brush->setColor(QColor(pen->color().red(),pen->color().green(),pen->color().blue(),pen->width() * 10));
        painter->setPen(QPen(QColor(pen->color().red(),pen->color().green(),pen->color().blue(),pen->width() * 10)));
        painter->setBrush(*brush);*/
        //painter->drawRect(QRect(m_x,m_y,m_w,m_h));

}


void Sepia::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void Sepia::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        update();
    }
    if(isActive){
        QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        update();
    }
}
void Sepia::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    update();
}
void Sepia::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Sepia::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Sepia::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
