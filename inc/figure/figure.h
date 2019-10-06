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
#include <QGraphicsScene>

class Figure : public QGraphicsItem{
protected:
    QCursor *m_hoverCursor;
    int m_zValue;
    float m_x,m_y,m_w,m_h;
    int figure;
    QPen *pen, *penActive;
    QBrush *brush,*brushActive;
    bool isActive;
    int cursorPosition;
    double m_scaleX,m_scaleY,m_translateX,m_translateY,m_angX,m_angY;
public:
    Figure();
    virtual bool setCursorP(QPointF pos);
    QRectF boundingRect() const;
    int positionForCursor(QPointF pos);
    int getPoint(QPointF p);
    virtual bool isPointColor(QPoint p);
    void setActive(bool active);
    void setColor(QColor color);
    void setWidthLine(int width);
    void enableBrush();
    void disableBrush();
};

#endif // FIGURE_H
