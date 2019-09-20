#include "inc\figure\figure.h"

Figure::Figure(){
    m_translateX = 0;m_translateY = 0;
    cursorPosition = 0;
    isActive = false;
    brush = new QBrush();
    pen = new QPen();
    brushActive = new QBrush(QColor(100,255,0,20));

    penActive = new QPen(QColor(100,255,0,255));
    penActive->setWidth(5);
    m_zValue = 5;
    setZValue(5);
}
QRectF Figure::boundingRect() const{
    int x,y,w,h;
    x = (m_w < 0?m_x + m_w:m_x)-10;
    w = (m_w < 0?-m_w:m_w)+20;
    y = (m_h < 0?m_y + m_h:m_y)-10;
    h = (m_h < 0?-m_h:m_h)+20;
    return QRectF(x, y, w, h);
}
void Figure::setColor(QColor color){
    QGraphicsItem::prepareGeometryChange();
    pen->setColor(color);
    brush->setColor(color);
    update();
}
void Figure::setWidthLine(int width){
    QGraphicsItem::prepareGeometryChange();
    pen->setWidth(width);
    update();
}
void Figure::enableBrush(){
    brush->setStyle(Qt::SolidPattern);
}
void Figure::disableBrush(){
    brush->setStyle(Qt::NoBrush);
}
void Figure::setActive(bool active){
    isActive = active;
    this->setZValue(active?8:m_zValue);
    QGraphicsItem::prepareGeometryChange();
    update();
}
