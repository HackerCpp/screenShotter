#include "inc/panel/btninsert.h"
#include <QPainter>

BtnInsert::BtnInsert(){

}
void BtnInsert::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QPixmap pixmap = icon().pixmap(iconSize());
    painter.drawPixmap(QRect((width()-pixmap.size().width())/2,(height() - pixmap.size().height())/2 - 5,pixmap.width(),pixmap.height()),pixmap);
}
