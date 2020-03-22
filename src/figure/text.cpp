#include "inc/figure/text.h"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QKeyEvent>
#include <QDebug>

bool Text::s_substrate = false;
void Text::transformation(QGraphicsSceneMouseEvent *event){
    QPointF p = prevPoints - event->scenePos();
    m_w -= p.x();
    m_h -= p.y();
}
void Text::staticSetSubstrate(int substrate){
    s_substrate = substrate?true:false;
}
int Text::getWidth(){
    return m_font->pointSize()-12;
}
Text::Text(int x,int y,int width, int height,QPen pen){
m_x =x;m_y = y;m_w = width;m_h = height;
m_text = "";
m_textOption = new QTextOption(Qt::AlignLeft | Qt::AlignTop);
    *this->pen = pen;
    close = true;
    prevPoints = QPointF(x,y);
    this->setFlag(QGraphicsItem::ItemIsFocusable,true);
    m_font = new QFont("Comic Sans MS",24);
    m_timer = new QTimer();
    //this->setActive(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    m_isEndLine = true;
    m_quantityLines = 1;
    m_substrate = false;
    m_strings = new QVector<QString>(1);
    m_numberBtn = 0;
    m_substrate = s_substrate;
    m_font->setPointSize(pen.width() - 2 + 12);
    QFontMetrics metric(*m_font);
    float w = 0;
    foreach (QString f_text, *m_strings) {
        w = (metric.width(f_text) <= w?w:(metric.width(f_text)+10));
    }
    m_w = w;
    m_h = metric.height() * m_quantityLines;
}
void Text::updateTimer(){
    m_isEndLine = !m_isEndLine;
    QGraphicsItem::prepareGeometryChange();
    update();
}
void Text::keyPressEvent(QKeyEvent *event) {
    if(!isActive)
        return;
    if(event->key() == Qt::Key_Escape){
        QGraphicsItem::keyPressEvent(event);
        return;
    }
    else if(event->key() == Qt::Key_Backspace){
        m_strings->last().chop(1);
        if(m_strings->last().size() == 0 && m_quantityLines > 1){
            --m_quantityLines;
            m_strings->pop_back();
        }
    }
    else if(event->key() == 16777220 || event->key() == Qt::Key_Enter){
        m_quantityLines++;
        m_strings->push_back("");
    }
    else{
        m_strings->last() += event->text();
    }
    QFontMetrics metric(*m_font);
    float w = 0;
    foreach (QString f_text, *m_strings) {
        w = (metric.width(f_text) <= w?w:(metric.width(f_text)+10));
    }
    m_w = w;
    m_h = metric.height() * m_quantityLines;
    QGraphicsItem::prepareGeometryChange();
    update();
    //qDebug() << "end";
 }
void Text::setActive(bool active){
    if(!active)
        close = false;
    isActive = active;
    QGraphicsItem::prepareGeometryChange();
    update();
    //this->setFocus();
}
bool Text::isPointColor(QPoint p){
    /*QImage image(scene()->width(),scene()->height(), QImage::Format_RGB32);
    image.fill(nullptr);
    QPainter painter(&image);
    QPen pe(Qt::white);
    pe.setWidth(pen->width());
    painter.setPen(pe);
    painter.setFont(*m_font);
    QString text;
    foreach (QString f_text, *m_strings) {
        text += f_text;
        text +="\n";
    }
    text.chop(1);
    if(isActive && m_isEndLine){
        text = text + "|";
    }

    painter.drawText(boundingRect(),text,*m_textOption);
    if(isActive){
        painter.drawEllipse(m_x-5,m_y-5,10,10);
        painter.drawEllipse(m_x+m_w-5,m_y-5,10,10);
        painter.drawEllipse(m_x-5,m_y+m_h-5,10,10);
        painter.drawEllipse(m_x+m_w-5,m_y+m_h-5,10,10);
    }
    QColor posColor = QColor(image.pixel(p.x(),p.y()));
    if (posColor == Qt::white){
         return true;
    }
    return false;*/
    return true;
}
void Text::setSubstrate(int substrate){
    m_substrate = substrate?true:false;
    this->setFocus();
}
void Text::setWidthLine(int width){
    m_font->setPointSize(width + 12);
    QFontMetrics metric(*m_font);
    float w = 0;
    foreach (QString f_text, *m_strings) {
        w = (metric.width(f_text) <= w?w:(metric.width(f_text)+10));
    }
    m_w = w;
    m_h = metric.height() * m_quantityLines;
    QGraphicsItem::prepareGeometryChange();
    update();
    this->setFocus();
}
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    QGraphicsItem::prepareGeometryChange();
       painter->setRenderHint(QPainter::Antialiasing);
        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        painter->setPen(*pen);
        painter->setBrush(*brush);
        painter->setFont(*m_font);
        QString text;
        foreach (QString f_text, *m_strings) {
            text += f_text;
            text +="\n";
        }
        text.chop(1);
        if(isActive && m_isEndLine){
            text = text + "|";
        }
        if(m_substrate){
            QBrush brush(QColor(245,245,245,255));
            QPen penR(QColor(245,245,245,255));
            painter->setPen(penR);
            painter->setBrush(brush);
            painter->drawRect(boundingRect());
            painter->setPen(*pen);
        }
        painter->drawText(boundingRect(),text,*m_textOption);
    if(isActive){
        painter->setPen(*penActive);
        painter->setBrush(*brushActive);
        painter->drawEllipse(m_x-5,m_y-5,10,10);
        painter->drawEllipse(m_x+m_w-5,m_y-5,10,10);
        painter->drawEllipse(m_x-5,m_y+m_h-5,10,10);
        painter->drawEllipse(m_x+m_w-5,m_y+m_h-5,10,10);
    }

}


void Text::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    else{
        cursorPosition = getPoint(event->pos());
        prevPoints = event->scenePos();
    }
}
void Text::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
    if(isActive){
        QPointF p = prevPoints - event->scenePos();
        if(cursorPosition == 2){
            m_w -= p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 3){
            m_x -= p.x();
            m_y -= p.y();
            m_w += p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 4){
            m_y -= p.y();
            m_w -= p.x();
            m_h += p.y();
        }
        else if(cursorPosition == 5){
            m_x -= p.x();
            m_w += p.x();
            m_h -= p.y();
        }
        else if(cursorPosition == 6){
            m_h += p.y();
            m_y -= p.y();
        }
        else if(cursorPosition == 7){
            m_h -= p.y();
        }
        else if(cursorPosition == 8){
            m_w += p.x();
            m_x -= p.x();
        }
        else if(cursorPosition == 9){
            m_w -= p.x();
        }
        else{
            m_x -= p.x();
            m_y -= p.y();
        }
        QGraphicsItem::prepareGeometryChange();
        prevPoints = event->scenePos();
        update();
    }
}
void Text::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(close){
        //close = false;
        isActive = true;
        m_timer->start(500);
    }
    QGraphicsItem::prepareGeometryChange();
    update();
}
void Text::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
void Text::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
}
void Text::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
}
