#ifndef PENANDBRUSH_H
#define PENANDBRUSH_H

#include "inc/figure/figure.h"
#include <QList>



class PenAndBrush : public Figure{
    QPointF lUp,lDown,rUp,rDown,prevPoints;
    bool close;
    QList<QPointF> m_points;
    QList<QPointF> m_pointsBegin;
    float x_min,x_max,y_min,y_max;
    float m_xBegin,m_yBegin,m_wBegin,m_hBegin;
    bool m_isPen;

public:
    PenAndBrush(int x,int y,QPen pen,bool isPen);
    //void setCursorP(QPointF pos);
    bool isPointColor(QPoint p);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PENANDBRUSH_H
