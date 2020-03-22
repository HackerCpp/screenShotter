#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H
#include <QTextEdit>
#include <QMenu>
#include <QPainter>
#include <QPaintEvent>
#include <QTabBar>

class ContextMenu :  public QMenu{
    Q_OBJECT
    QRect m_size;
    bool eventFilter(QObject * obj, QEvent *event);
public:
    ContextMenu(QWidget* pwgt = 0);
    //void paintEvent(QPaintEvent *event);

public slots:
signals:
    void save();
    void copy();
    void global();
};

#endif // CONTEXTMENU_H
