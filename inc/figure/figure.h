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
#include <QThread>

class Figure : public QThread,public QGraphicsItem{
    Q_OBJECT
protected:
    QImage *m_curentPixmap,*m_doublePixmap;
    QCursor *m_hoverCursor;
    int m_zValue;
    float m_x,m_y,m_w,m_h;
    int figure;
    QPen *pen, *penActive;
    QBrush *brush,*brushActive;
    bool isActive;
    int cursorPosition,m_numberBtn;
    double m_scaleX,m_scaleY,m_translateX,m_translateY,m_angX,m_angY;
    void virtual run();
    void swapPixMap();
public:
    Figure();
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual bool setCursorP(QPointF pos);
    QRectF boundingRect() const;
    int positionForCursor(QPointF pos);
    int getPoint(QPointF p);
    virtual bool isPointColor(QPoint p);
    virtual void setActive(bool active);
    virtual int getWidth();
    void setColor(QColor color);
    virtual void setWidthLine(int width);
    void enableBrush();
    void disableBrush();
    int getNumberBtn(){return m_numberBtn;}
};

#endif // FIGURE_H
