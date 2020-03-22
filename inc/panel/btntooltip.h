#ifndef BTNTOOLTIP_H
#define BTNTOOLTIP_H
#include <QPushButton>
#include <QLabel>
#include <QToolTip>
#include <QTimer>

class ToolTip : public QWidget{

public:
    ToolTip(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event)override;
};

class BtnToolTip : public QPushButton{
    Q_OBJECT
    QTimer *m_timer;
    int m_index;
    bool event(QEvent *e) override;
public:
    BtnToolTip(int index);
    ~BtnToolTip()override;
public slots:
    void showToolTip();
signals:
    void showToolTipP(QPoint pos,int index);
    void hideToolTipP();

};

#endif // BTNTOOLTIP_H
