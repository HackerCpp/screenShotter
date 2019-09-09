#ifndef CURTAIN_H
#define CURTAIN_H
#include <QGraphicsItem>

class Curtain : public QGraphicsItem {
    float x,y,w,h;
    int isClose;
    QPointF lUp,lDown,rUp,rDown;
    QPointF beginPoint,prevPoint;

public:
    Curtain(int x,int y,int width, int height);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CURTAIN_H
