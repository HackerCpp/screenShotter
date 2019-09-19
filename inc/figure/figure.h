#ifndef FIGURE_H
#define FIGURE_H
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QPoint>
#include <QDebug>

class Figure : public QGraphicsItem
{

protected:
    int m_zValue;
    float m_x,m_y,m_w,m_h;
    int figure;
    QPen *pen, *penActive;
    QBrush *brush,*brushActive;
    bool isActive;
    int cursorPosition;
    int m_translateX,m_translateY;
public:
    Figure();
    QRectF boundingRect() const;
    void setActive(bool active);
    void setColor(QColor color);
    void setWidthLine(int width);
    void enableBrush();
    void disableBrush();
};

#endif // FIGURE_H
