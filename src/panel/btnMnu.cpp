#include "inc/panel/btnMnu.h"
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QPicture>
#include <QMouseEvent>



BtnMnu::BtnMnu(){
    m_indent = 3;
}
void BtnMnu::mousePressEvent(QMouseEvent *e){
        showMenu();
}
void BtnMnu::showMenuT(){
    showMenu();
}
void BtnMnu::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(QPen(0x003200));
    painter.setBrush(QBrush(0x003200));
    QPolygon points;
    points << QPoint((width()-6) - m_indent,m_indent)
    << QPoint(width() - m_indent,m_indent)
    << QPoint(width() - m_indent,6 + m_indent);
    painter.drawPolygon(points);

}
