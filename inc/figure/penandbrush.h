#ifndef PENANDBRUSH_H
#define PENANDBRUSH_H

#include "inc/figure/figure.h"
#include <QList>
#include <QPainterPath>



class PenAndBrush : public Figure{
    QPointF lUp,lDown,rUp,rDown,prevPoints;
    bool close;
    QList<QPointF> m_points;
    QPainterPath m_path;
    QList<QPointF> m_pointsBegin;
    float x_min,x_max,y_min,y_max;
    float m_xBegin,m_yBegin,m_wBegin,m_hBegin;
    bool m_isPen;
    void run()override;
public:
    PenAndBrush(int x,int y,QPen pen,bool isPen);
    //void setCursorP(QPointF pos);
    bool isPointColor(QPoint p)override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
};

#endif // PENANDBRUSH_H
