#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QPushButton>
#include <QGroupBox>
#include <QSlider>
#include <QGridLayout>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QVector>
#include "inc/tabs/tabbase.h"

class Wind : public TabBase{
     Q_OBJECT


    QSystemTrayIcon *trayIcon;
    QGridLayout * gridLayoutUp;
    QHBoxLayout * hBoxLayoutAver,*hBoxLayoutDown;
    QGroupBox * groupBoxUp,* groupBoxAver;
    QWidget * downWidg;
    QPushButton * pushBtn[6];
    QLabel * labelleft,*labelRight;
    void setObgectName();
public:
    Wind();
    ~Wind();
signals:
    void enterFullScrin();
    void enterPartOfScreen();
    void enterSettings();
    void enterHistory();
    void enterOpen();
    void enterCopy();
public slots:
    void hideWin();
    void showWin();
    void destroy();
};


#endif // WINDOW_H
