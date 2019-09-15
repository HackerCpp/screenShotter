#ifndef PENANDBRUSH_H
#define PENANDBRUSH_H

#include "inc/figure/figure.h"
#include <QList>



class PenAndBrush : public Figure{
    QPointF lUp,lDown,rUp,rDown,prevPoints;
    bool close;
    QList<QPointF> m_points;
    float x_min,x_max,y_min,y_max;
    bool m_isPen;

public:
    PenAndBrush(int x,int y,QPen pen,bool isPen);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PENANDBRUSH_H
