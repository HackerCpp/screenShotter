#ifndef Text_H
#define Text_H
#include <QGraphicsItem>
#include "inc/figure/figure.h"
#include <QColor>
#include <QFont>
#include <QTimer>

class Text :public Figure {
    Q_OBJECT
    static bool s_substrate;
    QPointF prevPoints;
    QString m_text;
    QTextOption *m_textOption;
    QFont *m_font;
    bool close;
    QTimer *m_timer;
    bool m_isEndLine;
    int m_quantityLines;
    QVector<QString> *m_strings;
    bool m_substrate;
    QPixmap m_pixMap;

    void keyPressEvent(QKeyEvent *event)override;
    void transformation(QGraphicsSceneMouseEvent *event);
    void setActive(bool active)override;
public:
    static void staticSetSubstrate(int substrate);
    bool getSubstrate(){return m_substrate;}
    Text(int x,int y,int width, int height,QPen pen);
    bool isPointColor(QPoint p)override;
    void setWidthLine(int width)override;
     int getWidth()override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
public slots:
    void updateTimer();
    void setSubstrate(int substrate);
};

#endif // Text_H
