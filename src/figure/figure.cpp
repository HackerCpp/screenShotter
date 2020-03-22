#include "inc/figure/figure.h"
#include <QCursor>
#include "inc/screenscene.h"

Figure::Figure(){
    m_curentPixmap = new QImage(2000,2000,QImage::Format_ARGB32);
    m_doublePixmap = new QImage(2000,2000,QImage::Format_ARGB32);
    m_hoverCursor = new QCursor(QPixmap(":/res/cursors/Move"));
    m_scaleX = 1;m_scaleY = 1;
    m_translateX = 0;m_translateY = 0;
    m_angX = 0;m_angY = 0;
    cursorPosition = 0;
    isActive = false;
    brush = new QBrush();
    pen = new QPen();
    pen->setWidth(2);
    brushActive = new QBrush(QColor(100,255,0,200));
    penActive = new QPen(QColor(100,255,0,255));
    penActive->setWidth(2);
    m_numberBtn = 1;
    m_zValue = 5;
    setZValue(5);
}
void Figure::run(){

}
void Figure::swapPixMap(){
    QImage *ptr = m_curentPixmap;
    m_curentPixmap = m_doublePixmap;
    m_doublePixmap = ptr;
    ptr = nullptr;
    //scene()->update();
}
int Figure::getWidth(){
    return pen->width() - 2;
}
void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

}
int Figure::getPoint(QPointF p){
    for(int i_x = m_x+m_w/2 - 10;i_x<m_x+m_w/2+10;i_x++){
        for(int i_y =m_y+m_h/2-10;i_y < m_y+m_h/2+10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 1;
            }
        }
    }
    for(int i_x = m_x+m_w - 10;i_x<m_x+m_w+10;i_x++){
        for(int i_y =m_y+m_h-10;i_y < m_y+m_h+10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 2;
            }
        }
    }
    for(int i_x = m_x - 10;i_x<m_x + 10;i_x++){
        for(int i_y =m_y - 10;i_y < m_y + 10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 3;
            }
        }
    }
    for(int i_x = m_x+m_w - 10;i_x<m_x+m_w+10;i_x++){
        for(int i_y =m_y - 10;i_y < m_y + 10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 4;
            }
        }
    }
    for(int i_x = m_x - 10;i_x<m_x + 10;i_x++){
        for(int i_y =m_y+m_h-10;i_y < m_y+m_h+10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return  5;
            }
        }
    }
    for(int i_x = m_x+m_w/2-10;i_x<m_x+m_w/2+10;i_x++){
        for(int i_y = m_y - 10;i_y < m_y + 10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 6;
            }
        }
    }
    for(int i_x = m_x+m_w/2-10;i_x<m_x+m_w/2+10;i_x++){
        for(int i_y = m_y + m_h - 10;i_y < m_y + m_h + 10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 7;
            }
        }
    }
    for(int i_x = m_x-10;i_x<m_x+10;i_x++){
        for(int i_y = m_y + m_h/2 - 10;i_y < m_y + m_h/2 + 10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 8;
            }
        }
    }
    for(int i_x = m_x+m_w-10;i_x<m_x+m_w+10;i_x++){
        for(int i_y = m_y + m_h/2 - 10;i_y < m_y + m_h/2 + 10;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 9;
            }
        }
    }
    return 0;
}
bool Figure::isPointColor(QPoint p){
    ScreenScene *thisScene = dynamic_cast<ScreenScene*>(this->scene());
    QPixmap clenPixMap = thisScene->getCleanPixmap();
    QImage imageClen = clenPixMap.toImage();
    QImage image(scene()->width(),scene()->height(), QImage::Format_RGB32);
    QPainter painter(&image);
    this->scene()->render(&painter);
    QColor posColor = QColor(image.pixel(p.x(),p.y()));
    QColor cleanColor = QColor(imageClen.pixel(p.x(),p.y()));
    if (posColor != cleanColor){
         return true;
    }
    return false;
}
bool Figure::setCursorP(QPointF pos){
    bool position = false;
    if(isActive){
        int position = positionForCursor(pos);
        if(position == 2 || position == 3){
            setCursor(Qt::SizeFDiagCursor);
            position = true;
        }
        else if(position == 4 || position == 5){
            setCursor(Qt::SizeBDiagCursor);
            position = true;
        }
        else if(position == 6 || position == 7){
            setCursor(Qt::SizeVerCursor);
            position = true;
        }
        else if(position == 8 || position == 9){
            setCursor(Qt::SizeHorCursor);
            position = true;
        }
        else if(position == 1){
            setCursor(Qt::SizeAllCursor);
            position = true;
        }
        else {
            this->setCursor(Qt::ArrowCursor);
            position = false;
        }
    }
    else{
        if(isPointColor(QPoint(pos.x(),pos.y()))){
            this->setCursor(*this->m_hoverCursor);
            this->setZValue(this->m_zValue + 1);
            position = true;
        }
        else{
            this->setCursor(Qt::ArrowCursor);
            this->setZValue(m_zValue);
            position = false;
        }
    }
    return position;
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
    wait();
    pen->setColor(color);
    brush->setColor(color);
    this->setFocus();
    start();
}
int Figure::positionForCursor(QPointF p){
    if(isPointColor(QPoint(p.x(),p.y()))){
    int x = boundingRect().x();
    int y = boundingRect().y();
    int w = boundingRect().width();
    int h = boundingRect().height();
    int area = 10;
    for(int i_x = x+w - area;i_x<x+w+area;i_x++){
        for(int i_y =y+h-area;i_y < y+h+area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 2;
            }
        }
    }
    for(int i_x = x - area;i_x<x + area;i_x++){
        for(int i_y =y - area;i_y < y + area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 3;
            }
        }
    }
    for(int i_x = x+w - area;i_x<x+w+area;i_x++){
        for(int i_y =y - area;i_y < y + area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 4;
            }
        }
    }
    for(int i_x = x - area;i_x<x + area;i_x++){
        for(int i_y =y+h-area;i_y < y+h+area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return  5;
            }
        }
    }
    for(int i_x = x+w/2-area;i_x<x+w/2+area;i_x++){
        for(int i_y = y - area;i_y < y + area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 6;
            }
        }
    }
    for(int i_x = x+w/2-area;i_x<x+w/2+area;i_x++){
        for(int i_y = y + h - area;i_y < y + h + area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 7;
            }
        }
    }
    for(int i_x = x-area;i_x<x+area;i_x++){
        for(int i_y = y + h/2 - area;i_y < y + h/2 + area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 8;
            }
        }
    }
    for(int i_x = x+w-area;i_x<x+w+area;i_x++){
        for(int i_y = y + h/2 - 20;i_y < y + h/2 + area;i_y++){
            if(i_x == p.x() & i_y == p.y()){
                return 9;
            }
        }
    }

        return 1;
 }
    return 0;
}
void Figure::setWidthLine(int width){
    wait();
    QGraphicsItem::prepareGeometryChange();
    pen->setWidth(width+2);
    update();
    this->setFocus();
    start();
}
void Figure::enableBrush(){
    wait();
    brush->setStyle(Qt::SolidPattern);
    this->setFocus();
    start();
}
void Figure::disableBrush(){
    wait();
    brush->setStyle(Qt::NoBrush);
    this->setFocus();
    start();
}
void Figure::setActive(bool active){
    wait();
    isActive = active;
    QGraphicsItem::prepareGeometryChange();
    update();
    this->setFocus();
    start();
}
