#ifndef SCREENSCENE_H
#define SCREENSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QScreen>
#include <QGraphicsRectItem>
#include "panel.h"
class ScreenScene : public QGraphicsScene{
    int close;
    bool left_mouse;
    Panel *panel;
    QPointF     previousPoint;
    QGraphicsLineItem * horizontalLine;
    QGraphicsLineItem * verticalLine;
    QGraphicsRectItem *rectCentr;
    QGraphicsRectItem * rectIteam[8];
public:
    ScreenScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCREENSCENE_H
