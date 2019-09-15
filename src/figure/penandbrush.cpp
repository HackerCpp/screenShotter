#include "inc/figure/penandbrush.h"
#include <QPolygonF>
PenAndBrush::PenAndBrush(int x,int y,QPen pen,bool isPen){
    m_isPen = isPen;
    m_x = x;
    m_y = y;
    m_w = 1;
    m_h = 1;
    x_min = x_max = m_x;
    y_min = y_max = m_y;
    this->m_points.push_back(QPointF(x,y));
    *this->pen = pen;
    close = true;
    isActive = false;
}

void PenAndBrush::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
        if(isActive){

        }
        painter->setRenderHint(QPainter::Antialiasing,true);
        pen->setCosmetic(true);
        pen->setCapStyle(Qt::RoundCap);
        QPointF pointBegin = *m_points.begin();
        if(!m_isPen){
            pen->setColor(QColor(pen->color().red(),pen->color().green(),pen->color().blue(),150));
        };
        painter->setPen(*pen);
        painter->setBrush(*brush);
        QPainterPath path(pointBegin);
        for(auto point = m_points.begin()+1;point < m_points.end();point++){
            path.lineTo(*point);
        }
        painter->drawPath(path);
}


void PenAndBrush::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        this->m_points.push_back(event->pos());
        update();
    }
    else{
        prevPoints = event->scenePos();
    }
}
void PenAndBrush::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        this->m_points.push_back(event->pos());
        x_max = x_max < event->pos().x()?event->pos().x():x_max;
        x_min = x_min > event->pos().x()?event->pos().x():x_max;
        y_max = y_max < event->pos().y()?event->pos().y():y_max;
        y_min = y_min > event->pos().y()?event->pos().y():y_min;
        prevPoints = event->scenePos();
        update();
    }
    else if(isActive){
        QGraphicsItem::prepareGeometryChange();

        prevPoints = event->scenePos();
        update();
    }
}
void PenAndBrush::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    update();
}
void PenAndBrush::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void PenAndBrush::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void PenAndBrush::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
