#ifndef BTNSPANEL_H
#define BTNSPANEL_H

#include <QWidget>
#include "inc/panel/btn.h"
#include <QToolBar>
#include <QHBoxLayout>

class BtnsPanel :public QWidget{
    Q_OBJECT
    QVector<Btn *> *m_btn;
    QToolBar * m_toolBar;
    QHBoxLayout * m_hBoxLayout;
public:
    BtnsPanel();
};

#endif // BTNSPANEL_H
