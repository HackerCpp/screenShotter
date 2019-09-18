#ifndef Text_H
#define Text_H
#include <QGraphicsItem>
#include "inc\figure\figure.h"
#include <QColor>

class Text : public Figure , public QGraphicsTextItem {
    int m_number;
    QPointF prevPoints;
    bool close;

    void transformation(QGraphicsSceneMouseEvent *event);
public:
    Text(int x,int y,int width, int height,QPen pen,int number);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // Text_H
