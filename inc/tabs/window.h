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
#include "inc/tabs/tray.h"
#include <QVector>
#include "inc/tabs/tabbase.h"
#include "inc/tabs/btnsforurl.h"
#include <QMenu>

class Wind : public TabBase{
     Q_OBJECT
    Tray *trayIcon;
    QGridLayout * gridLayoutUp;
    QHBoxLayout *hBoxLayoutDown;
    QGroupBox * groupBoxUp;
    QWidget * downWidg;
    QPushButton * pushBtn[4];
    QLabel * labelleft,*labelRight;
    BtnsForUrl * m_btnForUrl;
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
