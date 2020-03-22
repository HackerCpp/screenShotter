#ifndef Arrow_H
#define Arrow_H
#include <QGraphicsItem>
#include "inc/figure/figure.h"
#include <QColor>

class Arrow : public Figure {
    QPointF prevPoints;
    bool close,tail;
    QVector<QPoint> *m_points;
    QVector<QPoint> *m_pointsBegin;
    int widthmin,widthmax,heightmin,heightmax;
    qreal length;

    void transformation(QGraphicsSceneMouseEvent *event);
    void transformationTwo(QGraphicsSceneMouseEvent *event);
    void updateP();
    void transform();
public:
    void setWidthLine(int width)override;
    int getWidth()override;
    Arrow(int x,int y,int width, int height,QPen pen);
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

#endif // Arrow_H
