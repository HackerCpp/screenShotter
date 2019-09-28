#ifndef SCREENSCENE_H
#define SCREENSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QScreen>
#include <QGraphicsRectItem>
#include "panel.h"
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include "inc\figure\figure.h"
#include "inc/communicationwithserver.h"

class ScreenScene : public QGraphicsScene{
    Q_OBJECT

    QColor tableColor[36]= {QColor(000,000,000),QColor(50,0,0),QColor(100,0,0),QColor(150,0,0),QColor(200,0,0),QColor(255,0,0),
                            QColor(255,50,0),QColor(255,100,0),QColor(255,150,0),QColor(255,200,0),QColor(255,255,0),
                       QColor(200,255,0),QColor(150,255,0),QColor(100,255,0),QColor(50,255,0),QColor(0,255,0),
                       QColor(0,255,50),QColor(0,255,100),QColor(0,255,150),QColor(0,255,200),QColor(0,255,255),
                       QColor(0,200,255),QColor(0,150,255),QColor(0,100,255),QColor(0,50,255),QColor(0,0,255),
                       QColor(50,0,255),QColor(100,0,255),QColor(150,0,255),QColor(200,0,255),
                       QColor(255,0,255),QColor(255,0,200),QColor(255,0,150),QColor(255,0,100),QColor(255,0,50),QColor(255,255,255)};
    QPen m_pen;
    Figure * curentFigure;
    int curentZ;
    float x,y,w,h;
    int isClose;
    QPixmap *m_pixMap;
    QPointF lUp,lDown,rUp,rDown;
    QPointF beginPoint,prevPoint;
    bool dravTekst;
    bool isCitrain;
    int numberSquare;
    QGraphicsPixmapItem *pixIteam;
    QPixmap pixmap;
    int close;
    bool left_mouse;
    Panel *panel;
    QPointF     previousPoint;
    QGraphicsLineItem * horizontalLine;
    QGraphicsLineItem * verticalLine;
    QGraphicsItem *rectCentr,*rectBlackWin;
    QGraphicsRectItem * rectIteam[8];
    QGraphicsSimpleTextItem * textItem;
    CommunicationWithServer m_server;
    int figure;
    void mouseClkClose(QGraphicsSceneMouseEvent *event);
    void mouseClkOpen(QGraphicsSceneMouseEvent *event);
    void mouseMoveBegin(QGraphicsSceneMouseEvent *event);
    void mouseMoveClose(QGraphicsSceneMouseEvent *event);
    void mouseMoveOpen(QGraphicsSceneMouseEvent *event);
    void mouseRelClose(QGraphicsSceneMouseEvent *event);
    void newFigure(QGraphicsSceneMouseEvent *event);
public:
    ScreenScene(bool isFullScreen);
    Panel * getPanel(){return panel;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    ~ScreenScene();
signals:
    void enterSavePixmap();
public slots:
    void savePixMap();
    void changeColor(int index);
    void changeWLine(int index);
    void changefigure(int index){figure = index;}
};

#endif // SCREENSCENE_H
