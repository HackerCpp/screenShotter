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
    pen->setColor(color);
    brush->setColor(color);
}
void Figure::setWidthLine(int width){
    pen->setWidth(width);
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
