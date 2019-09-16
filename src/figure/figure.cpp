#include "inc\figure\figure.h"

Figure::Figure(){
    isActive = false;
    brush = new QBrush();
    pen = new QPen();
}
QRectF Figure::boundingRect() const{
    return QRectF(m_x, m_y, m_w, m_h);
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
    QGraphicsItem::prepareGeometryChange();
    update();
}