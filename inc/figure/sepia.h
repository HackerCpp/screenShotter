#ifndef Sepia_H
#define Sepia_H
#include <QGraphicsItem>
#include "inc\figure\figure.h"
#include <QColor>

class Sepia : public Figure {
    int m_number;
    QPointF prevPoints;
    bool close,m_sepia;
    QPixmap m_pixMap;

    void transformation(QGraphicsSceneMouseEvent *event);
public:
    Sepia(int x,int y,int width, int height,QPen pen,QPixmap pixmap,bool sepia);
    bool setCursorP(QPointF pos);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // Sepia_H
