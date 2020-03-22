#include "inc/panel/slidersize.h"
#include <QDebug>

SliderSize::SliderSize(){
    m_count = 0;
    m_nullPer = new QImage(":/res/pict/0.png");
    m_oneHanPer = new QImage(":/res/pict/100.png");
    m_settings = new QSettings;
    setMaximum(255);
    setValue(m_settings->value("/Settings/Panel/Width").toInt());
    m_timer = new QTimer();
    connect(m_timer,&QTimer::timeout,this,&SliderSize::updateTimer);
    m_timer->start(400);
}
void SliderSize::mousePressEvent(QMouseEvent *ev){
    if(ev->x() < ((m_diameter/2) + 4) || ev->x() > (width() - (m_diameter/2) - 4))
        return;
    double wid = width() - m_diameter - 8;
    double x = ev->x() - (m_diameter/2) - 4;
    double max = maximum();
    this->setValue(max/(wid/x));
    update();
}
SliderSize::~SliderSize(){
   m_settings->setValue("/Settings/Panel/Width",value());
   delete m_settings;
   m_settings = nullptr;
}
void SliderSize::updateTimer(){
    m_count++;
   emit valueChanged(value());
    if(m_count > 6){
        m_timer->stop();
        delete m_timer;
    }
}
void SliderSize::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->x() < ((m_diameter/2) + 4) || ev->x() > (width() - (m_diameter/2) - 4))
        return;
    double wid = width() - m_diameter - 8;
    double x = ev->x() - (m_diameter/2) - 4;
    double max = maximum();
    this->setValue(max/(wid/x));
    update();
}
void SliderSize::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    double f_value = this->value();
    double f_maximum = this->maximum();
    double f_posX = ((width() - m_diameter - 8))/(f_maximum/f_value) + 4;
    painter.setPen(QPen(Qt::white,0.5));
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(QRectF(f_posX + m_diameter,(height()/2)-2,width() - f_posX - m_diameter - m_diameter/2,4));
    painter.setPen(QPen(Qt::white,0.5));
    painter.setBrush(QBrush(0x00FA9A));
    painter.drawRect(QRectF(m_diameter/2,(height()/2)-2,f_posX + m_diameter/2,4));
    painter.setPen(QPen(Qt::white));
    painter.setBrush(QBrush(Qt::white));
    QPen pen(Qt::white,7);
    painter.setPen(pen);
    painter.setBrush(QBrush());
    painter.drawEllipse(QRectF(f_posX ,(height()/2) - (m_diameter/2),m_diameter,m_diameter));
    painter.setFont(QFont("fnt"));
    painter.drawImage(QRect(m_nullPer->width(),height()- 10,m_nullPer->width(),m_nullPer->height()),*m_nullPer);
    painter.drawImage(QRect(width() - m_oneHanPer->width()-m_oneHanPer->width()/2,height()- 10,m_oneHanPer->width(),m_oneHanPer->height()),*m_oneHanPer);
    //painter.drawText(QRect(width()/2,height()-15,100,25),QString::number(value()/((double)maximum()/100)) + "%");
}
