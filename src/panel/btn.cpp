#include "inc/panel/btn.h"
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QPicture>
#include <QMouseEvent>



Btn::Btn(){

}
void Btn::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton)
        emit rightClick();
    else{
        emit clicked();
    }
}
void Btn::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QPixmap pixmap = icon().pixmap(iconSize());
    painter.drawPixmap(QRect((width()-pixmap.size().width())/2 + width()/8,(height() - pixmap.size().height())/2,pixmap.width(),pixmap.height()),pixmap);
}
