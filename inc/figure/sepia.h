#ifndef Sepia_H
#define Sepia_H
#include <QGraphicsItem>
#include "inc/figure/figure.h"
#include <QColor>

class Sepia : public Figure {
    Q_OBJECT
    int m_number;
    QPointF prevPoints;
    bool close,m_sepia;
    QPixmap m_pixMap;

    void transformation(QGraphicsSceneMouseEvent *event);
    void run() override;
public:
    void setWidthLine(int width)override;
    int getWidth()override;
    Sepia(int x,int y,int width, int height,QPen pen,QPixmap pixmap,bool sepia);
    bool setCursorP(QPointF pos)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    bool isSepia(){return m_sepia;}
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
signals:
    void changeWidthP(int width);
};

#endif // Sepia_H
