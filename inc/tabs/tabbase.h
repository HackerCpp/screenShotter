#ifndef TABBASE_H
#define TABBASE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class TabBase : public QWidget{
    Q_OBJECT

    QPoint m_previousPoint;
    bool m_active;
    QRect m_size;
    void setName();
protected:
    QHBoxLayout *headerLayout;
    QVBoxLayout * mainVBoxLayout;
    QLabel * headerLabelIcon,*headerLabelText;
    QPushButton * headerBtn;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void controlPosition();
public:
    TabBase();
public slots:
    virtual void hideWin();
};

#endif // TABBASE_H
