#ifndef SCREENSCENE_H
#define SCREENSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QScreen>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include "inc/figure/figure.h"
#include "inc/communicationwithserver.h"
#include <QSettings>

class ScreenScene : public QGraphicsScene{
    Q_OBJECT

    QString m_namePicture;
    QSettings m_settings;
    QPen m_pen;
    Figure * curentFigure;
    int curentZ,m_quantityCitrain;
    float x,y,w,h;
    int isClose;
    QPixmap *m_pixMap;
    QPointF lUp,lDown,rUp,rDown;
    QPointF beginPoint,prevPoint;
    bool dravTekst;
    bool isCitrain;
    bool m_isPainterFigure;
    int numberSquare;
    QGraphicsPixmapItem *pixIteam;
    QPixmap pixmap;
    int close;
    bool left_mouse;

    QPointF     previousPoint;
    QGraphicsLineItem * horizontalLine;
    QGraphicsLineItem * verticalLine;
    QGraphicsItem *rectCentr,*rectBlackWin;
    QGraphicsRectItem * rectIteam[8];
    QGraphicsSimpleTextItem * textItem;
    CommunicationWithServer m_server;
    int figure;
    QList<QGraphicsItem *>  listItems;
    QList<QGraphicsItem *> listItemsDeleted;
    int curentItems;
    void mouseClkClose(QGraphicsSceneMouseEvent *event);
    void mouseClkOpen(QGraphicsSceneMouseEvent *event);
    void mouseMoveBegin(QGraphicsSceneMouseEvent *event);
    void mouseMoveClose(QGraphicsSceneMouseEvent *event);
    void mouseMoveOpen(QGraphicsSceneMouseEvent *event);
    void mouseRelClose(QGraphicsSceneMouseEvent *event);
    void newFigure(QGraphicsSceneMouseEvent *event);
public:
    void keyPressEvent(QKeyEvent *event);
    void showHideCurt(bool hide);
    QPixmap getCleanPixmap(){return pixmap;}
    ScreenScene(bool isFullScreen);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    ~ScreenScene();
signals:
    void enterSavePixmap();
    void copyPixMap();
    void showPanel(int x,int y,int x2,int y2,int width,int height);
    void movePanel(int x,int y,int x2,int y2,int width,int height);
    void savePicture(QPixmap *pict);
    void activeFigure(int);
    void activeText(bool is);
    void removeBtn(bool isActive);
    void insertBtn(bool isActive);
    void changeWidthL(int width);
public slots:
    void changeWidth(int width);
    void hideLastFigure();
    void showLastFigure();
    void savePixMap();
    void changeColor(QColor color);
    void changeWLine(int index);
    void changefigure(int index);
    void savePicture();
    void copyPicture();
    void checkBoxClicked(int check);


};

#endif // SCREENSCENE_H
