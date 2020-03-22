#ifndef SLIDERCOLOR_H
#define SLIDERCOLOR_H

#include "inc/panel/baseslider.h"
#include <QSettings>

class SliderColor:public BaseSlider{
    Q_OBJECT
    QSettings *m_settings;
    int m_count;
    QTimer *m_timer;
    QImage *m_image;
    QColor getPixel(QPoint point);
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    virtual void paintEvent(QPaintEvent *event)override;
public:
    SliderColor();
    ~SliderColor();
signals:
    void cahngeColor(QColor color);
private slots:
    void updateTimer();

};

#endif // SLIDERCOLOR_H
