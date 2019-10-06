#ifndef Line_H
#define Line_H
#include <QGraphicsItem>
#include "inc\figure\figure.h"
#include <QColor>

class Line : public Figure{
    QPointF prevPoints;
    bool close;

    void transformation(QGraphicsSceneMouseEvent *event);
public:
    Line(int x,int y,int width, int height,QPen pen);
    bool isPointColor(QPoint p);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // Line_H
