#include "inc/panel/baseslider.h"


void BaseSlider::appliedStyle(){
    QString style = "QSlider::groove:horizontal{ \
            border: 0.5 solid white; 	 \
             border-radius: 4px;\
            height:6px;}";
    this->setStyleSheet(style);
}

void BaseSlider::mousePressEvent(QMouseEvent *ev){
    if(ev->x() < ((m_diameter/2) + 4) || ev->x() > (width() - (m_diameter/2) - 4))
        return;
    double wid = width() - m_diameter - 8;
    double x = ev->x() - (m_diameter/2) - 4;
    double max = maximum();
    this->setValue(max/(wid/x));
    update();
}
void BaseSlider::mouseMoveEvent(QMouseEvent *ev){
    if(ev->x() < ((m_diameter/2) + 4) || ev->x() > (width() - (m_diameter/2) - 4))
        return;
    double wid = width() - m_diameter - 8;
    double x = ev->x() - (m_diameter/2) - 4;
    double max = maximum();
    this->setValue(max/(wid/x));
    update();
}
void BaseSlider::paintEvent(QPaintEvent *event){
    QStylePainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QStyleOptionSlider opt;
    double f_value = this->value();
    double f_maximum = this->maximum();
    double f_posX = ((width() - m_diameter - 8))/(f_maximum/f_value) + 4;
    initStyleOption(&opt);
    opt.sliderValue = 0;
    opt.sliderPosition = 0;
    opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderTickmarks;
    painter.drawComplexControl(QStyle::CC_Slider, opt);
    QPen pen(Qt::white,7);
    painter.setPen(pen);
    painter.drawEllipse(QRectF(f_posX ,(height()/2) - (m_diameter/2),m_diameter,m_diameter));
}
BaseSlider::BaseSlider(QWidget *parent):QSlider(Qt::Horizontal,parent){
//appliedStyle();
    this->setValue(0);
    m_diameter = 12;
    this->setMinimumHeight(m_diameter*4);
    update();

}
