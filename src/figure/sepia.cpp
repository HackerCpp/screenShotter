#include "inc/figure/sepia.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QColor>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGuiApplication>
#include <QPixmap>
#include <inc/screenscene.h>


void Sepia::transformation(QGraphicsSceneMouseEvent *event){
    wait();
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
    start();
}
Sepia::Sepia(int x,int y,int width, int height,QPen pen,QPixmap pixmap,bool sepia){
    m_x =x;m_y = y;m_w = width;m_h = height;
    m_sepia = sepia;
    *this->pen = pen;
    close = true;
    m_pixMap = pixmap;
    prevPoints = QPointF(x,y);
    if(m_sepia)
        m_zValue = 0;
    else {
        m_zValue = 1;
    }
    setZValue(m_zValue);
    m_numberBtn = 2;
}
void Sepia::setWidthLine(int width){
    wait();
    if(m_sepia){
        QGraphicsItem::prepareGeometryChange();
        pen->setWidth(width+2);
        update();
        this->setFocus();
    }
    else{
        emit changeWidthP(width);
    }
    start();
}
int Sepia::getWidth(){
    return pen->width() - 2;
}
bool Sepia::setCursorP(QPointF pos){
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
            position = true;
        }
        else{
            position = false;
        }
    }
    return position;
}
Q_GUI_EXPORT void qt_blurImage( QPainter* p, QImage& blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
void Sepia::run(){
    //painter->setRenderHint(QPainter::Antialiasing);
    //painter->setRenderHint(QPainter::HighQualityAntialiasing);
    QPainter painter(m_doublePixmap);
    m_doublePixmap->fill(QColor(0,0,0,0));
        int w,h,x,y;
        x = m_w < 0?m_x + m_w:m_x;
        w = m_w < 0?-m_w:m_w;
        y = m_h < 0?m_y + m_h:m_y;
        h = m_h < 0?-m_h:m_h;
        w = w?w:1;
        h = h?h:1;

        if(m_sepia){
            QImage img(this->m_pixMap.toImage().copy(x-20,y,w+20,h+20));
            //painter->translate(x-20,y);
            QPixmap pixmap(w+20,h);
            QPainter *p = new QPainter(&pixmap);
            p->setRenderHint(QPainter::Antialiasing);
            p->setRenderHint(QPainter::HighQualityAntialiasing);
            qt_blurImage(p, img,pen->width()+4, true, false);
            painter.drawImage(QRect(x,y,w,h),img.copy(10,0,img.width()-10,img.height()-10));
            //painter->drawPixmap(QRect(x,y,w,h),pixmap);

            delete p;
        }
        else{
            /*ScreenScene * screenScene = dynamic_cast<ScreenScene*>(this->scene());
            screenScene->showHideCurt(true);
            //QImage image(w,h, QImage::Format_ARGB32_Premultiplied);
            //image.fill(NULL);
            //QPainter p(&image);
            scene()->render(&painter,QRect(x,y,w,h),QRect(x,y,w,h));
            //scene()->render(&painter,sceneBoundingRect(),sceneBoundingRect());
            painter.translate(x,y);
            //qt_blurImage(&painter, image,0, true, false );
            screenScene->showHideCurt(false);*/
        }
        if(isActive){
            if(m_sepia){
                painter.translate(x,y);
                painter.scale(2,2);
                painter.setPen(*penActive);
                painter.setBrush(*brushActive);
                painter.drawEllipse(0,0,2,2);
                painter.drawEllipse(0+w/2,0,2,2);
                painter.drawEllipse(0,0+h/2,2,2);
                painter.drawEllipse(0+w/2,0+h/2,2,2);

                painter.drawEllipse(0+w/4,0,2,2);
                painter.drawEllipse(0+w/4,0+h/2,2,2);
                painter.drawEllipse(0,0+h/4,2,2);
                painter.drawEllipse(0+w/2,0+h/4,2,2);
                painter.drawLine(0+w/4+2,0+h/4+2,0+w/4-2,0+h/4-2);
                painter.drawLine(0+w/4-2,0+h/4+2,0+w/4+2,0+h/4-2);
            }
            else{
                painter.setPen(*penActive);
                painter.setBrush(*brushActive);
                painter.drawEllipse(0,0,2,2);
                painter.drawEllipse(0+w,0,2,2);
                painter.drawEllipse(0,0+h,2,2);
                painter.drawEllipse(0+w,0+h,2,2);

                painter.drawEllipse(0+w/2,0,2,2);
                painter.drawEllipse(0+w/2,0+h,2,2);
                painter.drawEllipse(0,0+h/2,2,2);
                painter.drawEllipse(0+w,0+h/2,2,2);
                painter.drawLine(0+w/2+2,0+h/2+2,0+w/2-2,0+h/2-2);
                painter.drawLine(0+w/2-2,0+h/2+2,0+w/2+2,0+h/2-2);
            }
        }
    swapPixMap();
}
void Sepia::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    int w,h,x,y;
    x = m_w < 0?m_x + m_w:m_x;
    w = m_w < 0?-m_w:m_w;
    y = m_h < 0?m_y + m_h:m_y;
    h = m_h < 0?-m_h:m_h;
    w = w?w:1;
    h = h?h:1;
    if(m_sepia){
        painter->drawImage(QRect(x,y,w,h),*m_curentPixmap,QRect(x,y,w,h));
    }
    else{
        ScreenScene * screenScene = dynamic_cast<ScreenScene*>(this->scene());
        screenScene->showHideCurt(true);
        QImage image(w,h, QImage::Format_ARGB32_Premultiplied);
        image.fill(QColor(0,0,0,0));
        QPainter p(&image);
        scene()->render(&p,QRect(0,0,w,h),QRect(x,y,w,h));
        painter->translate(x,y);
        qt_blurImage(painter, image,0, true, false );
        screenScene->showHideCurt(false);
    }
}


void Sepia::mousePressEvent(QGraphicsSceneMouseEvent *event){
    wait();
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        cursorPosition = getPoint(event->pos());
        prevPoints = event->scenePos();
    }
    start();
}
void Sepia::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    wait();
    if(close){
        QGraphicsItem::prepareGeometryChange();
        transformation(event);
        prevPoints = event->scenePos();
        update();
    }
    if(isActive){
        QPointF p = prevPoints - event->scenePos();

        if(cursorPosition == 2){
            m_w -= p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 3){
            m_x -= p.x();
            m_y -= p.y();
            m_w += p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 4){
            m_y -= p.y();
            m_w -= p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 5){
            m_x -= p.x();
            m_w += p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 6){
            m_h += p.y();
            m_y -= p.y();
        }
        else if(cursorPosition == 7){
            m_h -= p.y();
        }
        else if(cursorPosition == 8){
            m_w += p.x();
            m_x -= p.x();
        }
        else if(cursorPosition == 9){
            m_w -= p.x();
        }
        else{
            m_x -= p.x();
            m_y -= p.y();
        }
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    start();
}
void Sepia::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    wait();
    if(close){
        close = false;
    }
    cursorPosition = 0;
    QGraphicsItem::prepareGeometryChange();
    update();
    start();
}
void Sepia::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Sepia::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Sepia::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
