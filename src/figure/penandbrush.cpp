#include "inc/figure/penandbrush.h"
#include <QPolygonF>
#include <QtMath>
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
        cursorPosition = getPoint(event->pos());
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
        QPointF p = prevPoints - event->scenePos();
        if(cursorPosition == 1){
            m_translateX -= p.x();
            m_translateY -= p.y();
        }
        else if(cursorPosition == 2){
            m_scaleX -= p.x()/(x_max - x_min);
            m_scaleY -= p.y()/(y_max - y_min);
            m_w -= p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 3){
            m_translateX -= p.x();
            m_translateY -= p.y();
            m_scaleX += p.x()/(x_max - x_min);
            m_scaleY += p.y()/(y_max - y_min);
            m_w += p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 4){
            m_translateY -= p.y();
            m_scaleX -= p.x()/(x_max - x_min);
            m_scaleY += p.y()/(y_max - y_min);
            m_w -= p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 5){
            m_translateX -= p.x();
            m_scaleX += p.x()/(x_max - x_min);
            m_scaleY -= p.y()/(y_max - y_min);
            m_w += p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 6){
            m_translateY -= p.y();
            m_scaleY += p.y()/(y_max - y_min);
            m_h += p.y();
        }
        else if(cursorPosition == 7){
            m_scaleY -= p.y()/(y_max - y_min);
            m_h -= p.y();
        }
        else if(cursorPosition == 8){
            m_translateX -= p.x();
            m_scaleX += p.x()/(x_max - x_min);
            m_w += p.x();
        }
        else if(cursorPosition == 9){
            m_scaleX -= p.x()/(x_max - x_min);
            m_w -= p.x();
        }
        int i = 0;
        for(auto pr = m_points.begin() ;pr < m_points.end();pr++ , i++){
            pr->setX(m_pointsBegin.at(i).x() * m_scaleX + m_translateX);
            pr->setY(m_pointsBegin.at(i).y() * m_scaleY + m_translateY);
        }
        m_x = m_xBegin * m_scaleX + m_translateX;
        m_y = m_yBegin * m_scaleY + m_translateY;

        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
}
void PenAndBrush::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        close = false;
        for(auto pr = m_points.begin();pr < m_points.end();pr++){
            QPointF point;
            point.setX(pr->x() - x_min);
            point.setY(pr->y() - y_min);
            m_pointsBegin.push_back(point);
        }
        m_translateX = x_min;
        m_translateY = y_min;
        m_xBegin = m_x - x_min;m_yBegin = m_y - y_min;
        m_wBegin = x_max - x_min;m_hBegin = y_max - y_min;
    }
    cursorPosition = 0;
    update();
}
void PenAndBrush::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void PenAndBrush::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void PenAndBrush::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
