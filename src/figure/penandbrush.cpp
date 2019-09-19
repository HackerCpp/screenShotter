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
        painter->translate(m_translateX,m_translateY);
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
        if(isActive){
          painter->setPen(*penActive);
          painter->setBrush(*brushActive);
          painter->drawEllipse(m_x-5,m_y-5,10,10);
          painter->drawEllipse(m_x+m_w-5,m_y-5,10,10);
          painter->drawEllipse(m_x-5,m_y+m_h-5,10,10);
          painter->drawEllipse(m_x+m_w-5,m_y+m_h-5,10,10);

          painter->drawEllipse(m_x+m_w/2,m_y-5,10,10);
          painter->drawEllipse(m_x+m_w/2,m_y+m_h-5,10,10);
          painter->drawEllipse(m_x-5,m_y+m_h/2,10,10);
          painter->drawEllipse(m_x+m_w-5,m_y+m_h/2,10,10);
          painter->drawLine(m_x+m_w/2-5,m_y+m_h/2-5,m_x+m_w/2+5,m_y+m_h/2+5);
          painter->drawLine(m_x+m_w/2-5,m_y+m_h/2+5,m_x+m_w/2+5,m_y+m_h/2-5);
          //painter->drawRect(boundingRect());
        }
}


void PenAndBrush::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        this->m_points.push_back(event->pos());
        update();
    }
    else{
        for(int i_x = m_x+m_w/2 - 10;i_x<m_x+m_w/2+10;i_x++){
            for(int i_y =m_y+m_h/2-10;i_y < m_y+m_h/2+10;i_y++){
                if(i_x == event->pos().x() & i_y == event->pos().y()){
                    cursorPosition = 1;
                }
            }
        }
        prevPoints = event->scenePos();
    }
}
void PenAndBrush::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        this->m_points.push_back(event->pos());
        x_max = x_max < event->pos().x()?event->pos().x():x_max;
        x_min = x_min > event->pos().x()?event->pos().x():x_min;
        y_max = y_max < event->pos().y()?event->pos().y():y_max;
        y_min = y_min > event->pos().y()?event->pos().y():y_min;
        m_x = x_min;
        m_y = y_min;
        m_w = x_max - x_min;
        m_h = y_max - y_min;

        prevPoints = event->scenePos();
        update();
    }
    else if(isActive){
        if(cursorPosition == 1){
            m_x -= prevPoints.x() - event->pos().x();
            m_y -= prevPoints.y() - event->pos().y();
            for(auto p = m_points.begin();p < m_points.end();p++){
                p->setX(p->x()-(prevPoints.x() - event->pos().x()));
                p->setY(p->y()-(prevPoints.y() - event->pos().y()));
            }
        }
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
}
void PenAndBrush::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close)
        close = false;
    cursorPosition = 0;
    update();
}
void PenAndBrush::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void PenAndBrush::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void PenAndBrush::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
