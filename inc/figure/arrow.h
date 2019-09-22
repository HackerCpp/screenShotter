#ifndef Arrow_H
#define Arrow_H
#include <QGraphicsItem>
#include "inc\figure\figure.h"
#include <QColor>

class Arrow : public Figure {
    QPointF prevPoints;
    bool close,tail;
    QVector<QPoint> *m_points;
    QVector<QPoint> *m_pointsBegin;
    int widthmin,widthmax,heightmin,heightmax;
    int length;
    void transformation(QGraphicsSceneMouseEvent *event);
    void transformationTwo(QGraphicsSceneMouseEvent *event);
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
