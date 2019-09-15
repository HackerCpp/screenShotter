#ifndef Ellips_H
#define Ellips_H
#include <QGraphicsItem>
#include "inc\figure\figure.h"
#include <QColor>

class Ellips : public Figure {
    QPointF prevPoints;
    bool close;

    void transformation(QGraphicsSceneMouseEvent *event);
public:
    Ellips(int x,int y,int width, int height,QPen pen);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // Ellips_H
