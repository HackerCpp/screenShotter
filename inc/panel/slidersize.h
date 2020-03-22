#ifndef SLIDERSIZE_H
#define SLIDERSIZE_H
#include "inc/panel/baseslider.h"
#include <QSettings>

class SliderSize:public BaseSlider{
    Q_OBJECT
    void appliedStyle();
    QSettings *m_settings;
    int m_count;
    QTimer *m_timer;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    QImage *m_nullPer,*m_oneHanPer;
public:
    SliderSize();
    ~SliderSize()override;
private slots:
    void updateTimer();
};

#endif // SLIDERSIZE_H
