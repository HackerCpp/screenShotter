#ifndef BASESLIDER_H
#define BASESLIDER_H

#include <QSlider>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QTimer>

class BaseSlider: public QSlider{
    void appliedStyle();
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
protected:
    int m_diameter;
public:
    BaseSlider(QWidget *parent = nullptr);
};

#endif // BASESLIDER_H
