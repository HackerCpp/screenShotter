#include "inc/screenscene.h"
#include <QGuiApplication>
#include <QCursor>
#include <QPixmap>
#include <QGraphicsLineItem>
#include "inc/figure/curtain.h"
#include "inc/figure/penandbrush.h"
#include "inc/figure/arrow.h"
#include "inc/figure/line.h"
#include "inc/figure/ellips.h"
#include "inc/figure/sepia.h"
#include "inc/figure/text.h"
#include <QGraphicsView>
#include <QString>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsBlurEffect>
#include <QTextCodec>
#include <QBuffer>
#include <QEvent>
#include <QApplication>
#include <QClipboard>
#include <QFileDialog>
#include <QRgb>
#include "inc/settings/activewindow.h"

void ScreenScene::keyPressEvent(QKeyEvent *event){
    QGraphicsScene::keyPressEvent(event);
}

void ScreenScene::checkBoxClicked(int check){
    Text::staticSetSubstrate(check);
    Text *text = dynamic_cast<Text*>(curentFigure);
    if(text)
        text->setSubstrate(check);
}
void ScreenScene::showHideCurt(bool hide){
    if(hide)
        rectBlackWin->hide();
    else
        rectBlackWin->show();
}
void ScreenScene::newFigure(QGraphicsSceneMouseEvent *event){
    Figure *v = nullptr;
    switch (figure) {
    case 2:{
        v = new PenAndBrush(event->scenePos().x(),event->scenePos().y(),m_pen,true);
        break;
    }
    case 3:{
        v = new PenAndBrush(event->scenePos().x(),event->scenePos().y(),m_pen,false);
        break;
    }
    case 4:{
        v = new Line(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 5:{
        v = new Arrow(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 6:{
        v = new Text(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 7:{
        v = new Ellips(event->scenePos().x(),event->scenePos().y(),1,1,m_pen);
        break;
    }
    case 8:{
        v = new Curtain(event->scenePos().x(),event->scenePos().y(),1,1,m_pen,0);
        break;
    }
    case 9:{
        v = new Curtain(event->scenePos().x(),event->scenePos().y(),1,1,m_pen,numberSquare++);
        break;
    }
    case 10:{
        v = new Sepia(event->scenePos().x(),event->scenePos().y(),1,1,m_pen,pixmap,true);
        break;
    }
    case 11:{
        v = new Sepia(event->scenePos().x(),event->scenePos().y(),1,1,m_pen,pixmap,false);
        ++m_quantityCitrain;
        changeWidth(m_pen.width()-2);
        connect(dynamic_cast<Sepia*>(v),&Sepia::changeWidthP,this,&ScreenScene::changeWidth);
        rectBlackWin->show();
        break;
    }
    default:{
        QList<QGraphicsItem *> itemList = items(event->scenePos());
        bool isFigure = false;
        foreach(QGraphicsItem *value,itemList){
            Figure * fig = dynamic_cast<Figure*>(value);
            if(fig){
                if(fig->isPointColor(QPoint(event->scenePos().x(),event->scenePos().y()))){
                    isFigure = true;
                    if(curentFigure != fig){
                        curentFigure->setActive(false);
                        curentFigure->setCursorP(QPointF(0,0));
                        this->curentFigure = fig;
                    }
                    this->curentFigure->setActive(true);
                    emit changeWidthL(curentFigure->getWidth() * 10);
                    Text* text = dynamic_cast<Text*>(curentFigure);
                    if(text){
                        emit activeText(text->getSubstrate());
                        Text::staticSetSubstrate(text->getSubstrate());
                    }
                    emit activeFigure(curentFigure->getNumberBtn());
                    break;
                }
             }
        }
        if(!isFigure)
            if(curentFigure){
                this->curentFigure->setActive(false);
                curentFigure->setCursorP(QPointF(0,0));
            }
        this->left_mouse = true;
        QGraphicsScene::mousePressEvent(event);
        break;
    }
    }

    if(v){
        emit removeBtn(true);
        listItems.push_back(v);
        if(curentFigure)
            curentFigure->setActive(false);
        curentFigure = v;
        addItem(v);
        v->show();
        QGraphicsScene::mousePressEvent(event);
        this->left_mouse = true;
        if(dynamic_cast<Sepia*>(v))
            m_isPainterFigure = true;
    }
    update();
}
void ScreenScene::mouseClkClose(QGraphicsSceneMouseEvent *event){
    verticalLine->hide();
    horizontalLine->hide();
    rectCentr->hide();
    close = 1;
    lUp = lDown = rUp = rDown = event->scenePos();
    QPointF point = rDown - lUp;
    QPen pen(Qt::white);
    pen.setWidthF(0.25);
    QBrush brush(QColor(0,0,0,100));
    textItem = addSimpleText("");

    rectIteam[0] = addRect(QRect().adjusted(0,0,lUp.x(),lUp.y()),pen,brush);
    rectIteam[1] = addRect(QRect().adjusted(lUp.x(),0,rUp.x(),rUp.y()),pen,brush);
    rectIteam[2] = addRect(QRect().adjusted(rUp.x(),0,width(),rUp.y()),pen,brush);
    rectIteam[3] = addRect(QRect().adjusted(rUp.x(),rUp.y(),width(),rDown.y()),pen,brush);
    rectIteam[4] = addRect(QRect().adjusted(rDown.x(),rDown.y(),width(),height()),pen,brush);
    rectIteam[5] = addRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),height()),pen,brush);
    rectIteam[6] = addRect(QRect().adjusted(0,lDown.y(),lDown.x(),height()),pen,brush);
    rectIteam[7] = addRect(QRect().adjusted(0,lUp.y(),lDown.x(),lDown.y()),pen,brush);
    for(int i = 0;i<8;i++){
        rectIteam[i]->setZValue(10);
    }
    beginPoint = event->scenePos();
    this->left_mouse = true;
}
void ScreenScene::mouseClkOpen(QGraphicsSceneMouseEvent *event){
    isCitrain = false;
    for(int i = 0;i<8;i++){
        if(itemAt(event->scenePos(),QTransform()) == rectIteam[i]){
            isCitrain = true;
            break;
        }
    }
    if(!isCitrain){
        newFigure(event);
        return;
    }
    prevPoint = event->scenePos();
    this->left_mouse = true;
    textItem->show();
}
void ScreenScene::mouseMoveBegin(QGraphicsSceneMouseEvent *event){
    this->verticalLine->setLine(event->scenePos().x(),0,event->scenePos().x(),this->height()-2);
    this->horizontalLine->setLine(0,event->scenePos().y(),this->width()-2,event->scenePos().y());
}
void ScreenScene::mouseMoveClose(QGraphicsSceneMouseEvent *event){
    textItem->show();
     if(event->scenePos().x() > beginPoint.x() & event->scenePos().y() > beginPoint.y()){
         lDown.setY(event->scenePos().y());
         rUp.setX(event->scenePos().x());
         rDown = event->scenePos();
     }
     else if(event->scenePos().x() < beginPoint.x() & event->scenePos().y() < beginPoint.y()){
         rUp.setY(event->scenePos().y());
         lDown.setX(event->scenePos().x());
         lUp = event->scenePos();
     }
     else if(event->scenePos().x() < beginPoint.x() & event->scenePos().y() > beginPoint.y()){
         rDown.setY(event->scenePos().y());
         lUp.setX(event->scenePos().x());
         lDown = event->scenePos();
     }
     else if(event->scenePos().x() > beginPoint.x() & event->scenePos().y() < beginPoint.y()){
         lUp.setY(event->scenePos().y());
         rDown.setX(event->scenePos().x());
         rUp = event->scenePos();
     }
     rectIteam[0]->setRect(QRect().adjusted(0,0,lUp.x(),lUp.y()));
     rectIteam[1]->setRect(QRect().adjusted(lUp.x(),0,rUp.x(),rUp.y()));
     rectIteam[2]->setRect(QRect().adjusted(rUp.x(),0,width(),rUp.y()));
     rectIteam[3]->setRect(QRect().adjusted(rUp.x(),rUp.y(),width(),rDown.y()));
     rectIteam[4]->setRect(QRect().adjusted(rDown.x(),rDown.y(),width(),height()));
     rectIteam[5]->setRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),height()));
     rectIteam[6]->setRect(QRect().adjusted(0,lDown.y(),lDown.x(),height()));
     rectIteam[7]->setRect(QRect().adjusted(0,lUp.y(),lDown.x(),lDown.y()));
     textItem->setPos(rDown.x()+10,rDown.y()-30);
     QPen pen(Qt::white);
     QBrush brush(Qt::white);
     pen.setWidth(0.1);
     textItem->setPen(pen);
     textItem->setBrush(brush);
     textItem->setFont(QFont("Courier", 15));
     textItem->setText(QString::number(rUp.x() - lUp.x()) + "x" + QString::number(rDown.y() - rUp.y()));
     textItem->setZValue(11);
}
void ScreenScene::mouseMoveOpen(QGraphicsSceneMouseEvent *event){
    if(!isCitrain){
        QGraphicsScene::mouseMoveEvent(event);
        update();
        return;
    }

     QPointF p = prevPoint - event->scenePos();
     if(prevPoint.x() < lUp.x()){
         lUp.setX(lUp.x()-p.x());
         lDown.setX(lDown.x()-p.x());
     }
     if(prevPoint.x() > rUp.x()){
         rUp.setX(rUp.x()-p.x());
         rDown.setX(rDown.x()-p.x());
     }
     if(prevPoint.y() > rDown.y()){
         rDown.setY(rDown.y()-p.y());
         lDown.setY(lDown.y()-p.y());
     }
     if(prevPoint.y() < rUp.y()){
         rUp.setY(rUp.y()-p.y());
         lUp.setY(lUp.y()-p.y());
     }
     if(lUp.x() >= rUp.x()){
         lUp.setX(rUp.x());
         rDown.setX(lDown.x());
         lDown.setX(lUp.x());
         rUp.setX(rDown.x());
     }
     if(lUp.y() >= lDown.y()){
         lUp.setY(lDown.y());
         rDown.setY(rUp.y());
         lDown.setY(rDown.y());
         rUp.setY(lUp.y());
     }
     rectIteam[0]->setRect(QRect().adjusted(0,0,lUp.x(),lUp.y()));
     rectIteam[1]->setRect(QRect().adjusted(lUp.x(),0,rUp.x(),rUp.y()));
     rectIteam[2]->setRect(QRect().adjusted(rUp.x(),0,width(),rUp.y()));
     rectIteam[3]->setRect(QRect().adjusted(rUp.x(),rUp.y(),width(),rDown.y()));
     rectIteam[4]->setRect(QRect().adjusted(rDown.x(),rDown.y(),width(),height()));
     rectIteam[5]->setRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),height()));
     rectIteam[6]->setRect(QRect().adjusted(0,lDown.y(),lDown.x(),height()));
     rectIteam[7]->setRect(QRect().adjusted(0,lUp.y(),lDown.x(),lDown.y()));
     textItem->setPos(rDown.x()+10,rDown.y()-30);
     textItem->setText(QString::number(rUp.x() - lUp.x()) + "x" + QString::number(rDown.y() - rUp.y()));
     prevPoint = event->scenePos();
     emit movePanel(rDown.x(),rDown.y(),rUp.x(),rUp.y(),width(),height());
     update();
}
void ScreenScene::mouseRelClose(QGraphicsSceneMouseEvent *event){
    rectIteam[0]->setCursor(QCursor(QPixmap(":/res/cursors/DiagonalResize1")));
    rectIteam[1]->setCursor(QCursor(QPixmap(":/res/cursors//VerticalResize")));
    rectIteam[2]->setCursor(QCursor(QPixmap(":/res/cursors//DiagonalResize2")));
    rectIteam[3]->setCursor(QCursor(QPixmap(":/res/cursors//HorizontalResize")));
    rectIteam[4]->setCursor(QCursor(QPixmap(":/res/cursors//DiagonalResize1")));
    rectIteam[5]->setCursor(QCursor(QPixmap(":/res/cursors//VerticalResize")));
    rectIteam[6]->setCursor(QCursor(QPixmap(":/res/cursors//DiagonalResize2")));
    rectIteam[7]->setCursor(QCursor(QPixmap(":/res/cursors//HorizontalResize")));
    //Вставить панель
    close = 2;
}

ScreenScene::ScreenScene(bool isFullScreen){
    m_isPainterFigure = false;
    m_pixMap = nullptr;
    numberSquare = 1;
    m_quantityCitrain = 0;
    curentFigure = nullptr;

    curentItems = -1;
    if(isFullScreen){
        close = 2;
        lUp = QPointF(0,0);
        lDown = QPointF(0,this->height()-1);
        rUp = QPointF(this->width()-1,0);
        rDown = QPointF(this->width()-1,this->height()-1);
        QPen pen(Qt::white);
        pen.setWidthF(0.25);
        QBrush brush(QColor(0,0,0,100));
        textItem = addSimpleText("");
        rectIteam[0] = addRect(QRect().adjusted(-1,-1,lUp.x(),lUp.y()),pen,brush);
        rectIteam[1] = addRect(QRect().adjusted(lUp.x(),-1,rUp.x(),rUp.y()),pen,brush);
        rectIteam[2] = addRect(QRect().adjusted(rUp.x(),-1,width()+1,rUp.y()),pen,brush);
        rectIteam[3] = addRect(QRect().adjusted(rUp.x(),rUp.y(),width()+1,rDown.y()),pen,brush);
        rectIteam[4] = addRect(QRect().adjusted(rDown.x(),rDown.y(),width()+1,height()+1),pen,brush);
        rectIteam[5] = addRect(QRect().adjusted(lDown.x(),lDown.y(),rDown.x(),height()+1),pen,brush);
        rectIteam[6] = addRect(QRect().adjusted(-1,lDown.y(),lDown.x(),height()+1),pen,brush);
        rectIteam[7] = addRect(QRect().adjusted(-1,lUp.y(),lDown.x(),lDown.y()),pen,brush);
        for(int i = 0;i<8;i++){
            rectIteam[i]->setZValue(10);
        }
    }
    else
        close = 0;
    figure = 0;
    if(m_settings.value("/Settings/Base/isNameActiveWindow").toBool()){
        m_namePicture = ActiveWindow::getActiveWndTitle().remove(".").remove(" ");
        if(m_namePicture.isEmpty())
            m_namePicture = "NAW" + QString::number(rand()%1999);
    }
    else
        m_namePicture = QString::number(rand()%1999);
    m_namePicture += ".png";
    QScreen *screen = QGuiApplication::primaryScreen();
    pixmap = screen->grabWindow(0);
    QCursor * cursor = new QCursor(QPixmap(":/res/cursors/Precision"));
    pixIteam = this->addPixmap(pixmap);
    pixIteam->setZValue(-10);
    rectBlackWin = addRect(QRect(0,0,width(),height()),QPen(QColor(0,0,0,100)),QBrush(QColor(0,0,0,220)));
    rectBlackWin->hide();
    rectBlackWin->setZValue(1);
    if(!isFullScreen){
        rectCentr = addRect(QRect(0,0,width(),height()),QPen(QColor(0,0,0,100)),QBrush(QColor(0,0,0,100)));
        QPen pen(Qt::white);
        pen.setWidthF(0.25);
        horizontalLine = this->addLine(QLineF(0,this->height()/2,this->width(),this->height()/2),pen);
        verticalLine = this->addLine(QLineF(this->width()/2,0,this->width()/2,this->height()),pen);
        horizontalLine->setCursor(*cursor);
        verticalLine->setCursor(*cursor);
    }
    m_pen.setWidth(2);
}

void ScreenScene::savePixMap(){
    if(curentFigure)
        this->curentFigure->setActive(false);
    update();
    QString email,password;
    QTextCodec *codec = QTextCodec::codecForMib(1015);
    email = m_settings.value(("/Settings/Autho/Email")).toString();
    email = codec->toUnicode(QByteArray::fromHex(email.toLocal8Bit()));
    password = m_settings.value(("/Settings/Autho/Password")).toString();
    password = codec->toUnicode(QByteArray::fromHex(password.toLocal8Bit()));
    QPixmap pixMap = views().back()->grab(QRect(lUp.x(),lUp.y(),rUp.x()-lUp.x(),lDown.y() - lUp.y()));
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixMap.save(&buffer, "PNG");
    QString path = m_settings.value("/Settings/Base/pathForSave").toString();
    if(!path.isEmpty())
        pixMap.save(path + m_namePicture ,"PNG");
    QString urlPict = m_server.sendPicture(email,password,bArray,m_namePicture).remove("\\");
    QString file = "platforms/QURL.dll";
    QFile out( file );
    if( out.open( QIODevice::WriteOnly ) ){
         QTextStream stream( &out );
         stream << urlPict;
         out.close();
     }
    if(m_settings.value("/Settings/Base/isGetUrl").toBool())
        QApplication::clipboard()->setText(urlPict);
    emit enterSavePixmap();
}
void ScreenScene::savePicture(){
    if(curentFigure)
        this->curentFigure->setActive(false);
    update();
    QPixmap pixMap = views().back()->grab(QRect(lUp.x(),lUp.y(),rUp.x()-lUp.x(),lDown.y() - lUp.y()));
    emit savePicture(&pixMap);
}
void ScreenScene::copyPicture(){
    if(curentFigure)
        this->curentFigure->setActive(false);
    update();
    QPixmap pixMap = views().back()->grab(QRect(lUp.x(),lUp.y(),rUp.x()-lUp.x(),lDown.y() - lUp.y()));

    QApplication::clipboard()->setPixmap(pixMap);
    emit copyPixMap();
}
void ScreenScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!close){
       mouseClkClose(event);
    }
    if(close == 1){
        prevPoint = event->scenePos();
        this->left_mouse = true;
        textItem->show();
    }
    if(close == 2){
        mouseClkOpen(event);
    }
}
void ScreenScene::changefigure(int index){
    figure = index;
    if(index == 1){
        if(curentFigure){
            curentFigure->setActive(false);
            curentFigure->setActive(true);
            emit activeFigure(curentFigure->getNumberBtn());
            update();
        }
        return;
    }
    if(curentFigure){
        curentFigure->setActive(false);
        curentFigure->setCursorP(QPointF(0,0));
        update();
    }
}
void ScreenScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_isPainterFigure){
        Figure * figure = dynamic_cast<Figure*>(curentFigure);
        if(figure)
            figure->mouseMoveEvent(event);
    }

   if(!close){
       this->verticalLine->setLine(event->scenePos().x(),0,event->scenePos().x(),this->height()-2);
       this->horizontalLine->setLine(0,event->scenePos().y(),this->width()-2,event->scenePos().y());
        //mouseMoveBegin(event);
        //update();
    }
   else if(close == 1){
       if(left_mouse){
           mouseMoveClose(event);
       }
   }
   else if (close == 2){
       if(left_mouse){
           mouseMoveOpen(event);
       }
       else{
           if(figure == 1){
                QList<QGraphicsItem *> itemList = items(event->scenePos());
                foreach(QGraphicsItem *value,itemList){
                    Figure * fig = dynamic_cast<Figure*>(value);
                    if(fig){
                        if(fig->setCursorP(event->scenePos())){
                            return;
                        }
                    }
                }
           }
       }
   }
   update();
}
void ScreenScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    m_isPainterFigure = false;
    if (this->left_mouse){
        this->left_mouse = false;
        textItem->hide();
        if(close == 1){
            emit showPanel(rDown.x(),rDown.y(),rUp.x(),rUp.y(),width(),height());
            mouseRelClose(event);
        }
        else if(close == 2){

        }
        QGraphicsScene::mouseReleaseEvent(event);
    }
    update();
}

void ScreenScene::changeColor(QColor color){
    m_pen.setColor(color);
    if(curentFigure)
        curentFigure->setColor(m_pen.color());
    update();
}
void ScreenScene::changeWLine(int index){
    this->m_pen.setWidthF(index/10+2);
    if(curentFigure)
        curentFigure->setWidthLine(index/10);
    update();
}
void ScreenScene::changeWidth(int width){
    rectBlackWin->setOpacity(0.03*width + 0.3);
}
void ScreenScene::hideLastFigure(){
    if(this->listItems.isEmpty())
        return;
    Sepia * sItem = dynamic_cast<Sepia*>(this->listItems.last());
    if(sItem){
        if(!sItem->isSepia()){
            --m_quantityCitrain;
            if(m_quantityCitrain == 0)
                this->rectBlackWin->hide();
        }

    }
    this->listItemsDeleted.push_back(this->listItems.last());
    this->listItems.last() = nullptr;
    this->listItems.pop_back();
    this->listItemsDeleted.last()->hide();
    if(!listItemsDeleted.isEmpty())
        emit insertBtn(true);
    if(listItems.isEmpty())
        emit removeBtn(false);
    update();
}
void ScreenScene::showLastFigure(){
    if(this->listItemsDeleted.isEmpty())
        return;
    listItems.push_back(listItemsDeleted.last());
    listItemsDeleted.last() = nullptr;
    listItemsDeleted.pop_back();
    if(dynamic_cast<Sepia*>(this->listItems.last())){
        this->rectBlackWin->show();
        ++m_quantityCitrain;
    }
    listItems.last()->show();
    if(listItemsDeleted.isEmpty())
        emit insertBtn(false);
    if(!listItems.isEmpty())
        emit removeBtn(true);
    update();
}
ScreenScene::~ScreenScene(){
    this->deleteLater();
}
