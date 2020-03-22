#ifndef Line_H
#define Line_H
#include <QGraphicsItem>
#include "inc/figure/figure.h"
#include <QColor>
#include <QThread>
#include <QImage>

class Line : public Figure{
    QPointF prevPoints;
    bool close;
    QPainter *m_painter;


    void transformation(QGraphicsSceneMouseEvent *event);
    void run() override;
public:
    Line(int x,int y,int width, int height,QPen pen);
    bool isPointColor(QPoint p)override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
};

#endif // Line_H
