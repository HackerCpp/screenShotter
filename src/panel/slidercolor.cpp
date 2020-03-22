#include "inc/panel/slidercolor.h"
#include <QPainter>
#include <QRgb>
#include <QMouseEvent>
#include <QDebug>
#include <QStylePainter>
#include <QStyleOptionSlider>


SliderColor::SliderColor(){
    m_count = 0;
    m_settings = new QSettings;
    m_image = new QImage(":/res/pict/color.png");
    setMaximum(380);
    setValue(m_settings->value("/Settings/Panel/Color").toInt());
    m_timer = new QTimer();
    connect(m_timer,&QTimer::timeout,this,&SliderColor::updateTimer);
    m_timer->start(400);
}
void SliderColor::mousePressEvent(QMouseEvent *ev){
    if(ev->x() < ((m_diameter/2) + 4) || ev->x() > (width() - (m_diameter/2) - 4))
        return;
    double wid = width() - m_diameter - 8;
    double x = ev->x() - (m_diameter/2) - 4;
    double max = maximum();
    this->setValue(max/(wid/x));

    /*double f_value = value();
    double f_posX = (wid)/(max/f_value) + 4;
    qDebug() << "Mouse x: " << ev->x() << " Counted: " << static_cast<int>(f_posX + (m_diameter/2) + 0.5) << " value: " << value();*/
    emit cahngeColor(getPixel(QPoint(ev->x(),height()/2)));
    update();
}
void SliderColor::updateTimer(){
    m_count++;
    double f_value = value();
    double f_posX = (width() - m_diameter - 8)/(maximum()/f_value) + 4;
    //qDebug() <<static_cast<int>(f_posX + (m_diameter/2) + 0.5);

    emit cahngeColor(getPixel(QPoint(static_cast<int>(f_posX + (m_diameter/2) + 0.5),height()/2)));
    if(m_count > 6){
        m_timer->stop();
        delete m_timer;
    }
}
void SliderColor::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->x() < ((m_diameter/2) + 4) || ev->x() > (width() - (m_diameter/2) - 4))
        return;
    double wid = width() - m_diameter - 8;
    double x = ev->x() - (m_diameter/2) - 4;
    double max = maximum();
    this->setValue(max/(wid/x));

    /*double f_value = value();
    double f_posX = (wid)/(max/f_value) + 4;
    qDebug() << "Mouse x: " << ev->x() << " Counted: " << static_cast<int>(f_posX + (m_diameter/2) + 0.5) << " value: " << value();*/
    emit cahngeColor(getPixel(QPoint(ev->x(),height()/2)));
    update();
}
void SliderColor::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    double f_value = this->value();
    double f_maximum = this->maximum();
    double f_posX = ((width() - m_diameter - 8))/(f_maximum/f_value) + 4;
    painter.drawImage(QRect(m_diameter/2,(height()/2) - 10,width() - m_diameter,20),*m_image);
    QPen pen(Qt::white,7);
    painter.setPen(pen);
    painter.drawEllipse(QRectF(f_posX ,(height()/2) - (m_diameter/2),m_diameter,m_diameter));
}
QColor SliderColor::getPixel(QPoint point){
   return this->grab(QRect(0,0,width(),height())).toImage().pixel(point);
}
SliderColor::~SliderColor(){
    if(m_image)
        delete m_image;
    m_image = nullptr;
    m_settings->setValue("/Settings/Panel/Color",value());
    delete m_settings;
    m_settings = nullptr;

}
