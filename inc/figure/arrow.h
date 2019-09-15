#ifndef Arrow_H
#define Arrow_H
#include <QGraphicsItem>
#include "inc\figure\figure.h"
#include <QColor>

class Arrow : public Figure {
    QPointF prevPoints;
    bool close;
    QVector<QPoint> *points;

    void transformation(QGraphicsSceneMouseEvent *event);
public:
    Arrow(int x,int y,int width, int height,QPen pen);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // Arrow_H
