#include "inc/panel/btnspanel.h"
#include <QDebug>
#include <QPainter>
#include <QRgb>

BtnsPanel::BtnsPanel(){
    QImage img("D:\\Project\\ScreenShot\\screenShot\\skrinshotter_kvork\\pict\\pen.png");
    QImage image(img.width(),img.height(), QImage::Format_ARGB32_Premultiplied);
    image.fill(0x00ffffff);
    QPainter painter(&image);
    painter.setPen(QPen(Qt::black));
    for(int i = 0; i < img.width(); i++){
        for(int j = 0; j < img.height();j++){
            QRgb rgb = img.pixel(i,j);
            painter.drawPoint(i,j);

        }
    }
    image.save("D:\\Project\\ScreenShot\\screenShot\\skrinshotter_kvork\\pict\\pen2.png");

    m_btn = new QVector<Btn*>;
    m_btn->push_back( new Btn(":/res/pict/arr.png"));
    m_btn->push_back( new Btn(":/res/pict/pen.png"));
    m_btn->push_back( new Btn(":/res/pict/brush.png"));
    m_btn->push_back( new Btn(":/res/pict/ell.png"));
    m_btn->push_back( new Btn(":/res/pict/rect.png"));
    m_btn->push_back( new Btn(":/res/pict/arrow.png"));
    m_btn->push_back( new Btn(":/res/pict/line.png"));
    m_btn->push_back( new Btn(":/res/pict/num.png"));
    m_btn->push_back( new Btn(":/res/pict/sep.png"));
    m_btn->push_back( new Btn(":/res/pict/cit.png"));
    m_btn->push_back( new Btn(":/res/pict/text.png"));
    m_hBoxLayout = new QHBoxLayout();
    this->setLayout(m_hBoxLayout);
    m_toolBar = new QToolBar();
    m_hBoxLayout->addWidget(m_toolBar);
    foreach(auto btn,*m_btn){
        btn->setMinimumSize(QSize(50,50));
        m_toolBar->addWidget(btn);
        m_toolBar->addSeparator();
    }
}
