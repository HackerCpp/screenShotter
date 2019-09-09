#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>

class Panel : public QWidget
{
    bool active;
    QVBoxLayout *vBoxLayout;
    QToolBar *toolBar;
    QPoint     previousPoint;
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

public slots:
    void set();
};

#endif // PANEL_H
