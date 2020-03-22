#ifndef MEN_H
#define MEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QPushButton>
#include <QGroupBox>
#include "inc/panel/baseslider.h"
#include <QGridLayout>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QVector>
#include "inc/tabs/contextmenu.h"
#include <QCheckBox>
#include "inc/panel/slidercolor.h"
#include "inc/panel/slidersize.h"
#include "inc/panel/btn.h"
#include "inc/panel/btnMnu.h"
#include "inc/panel/btntooltip.h"

class Panel : public QWidget{
    Q_OBJECT
    QSettings *m_settings;
    int thisWidth,thisHeight,heightCheckBox;
    BtnToolTip *prevBtnInd;
    QPoint previousPoint;
    bool showDown;
    bool active;
    SliderSize *slyderThickness;
    SliderColor *slyderColor;
    QHBoxLayout * slydersLayout;
    ContextMenu *m_menu;
    QWidget *m_how;
    int m_btnWidth,m_howWidth,m_btnEnterWidth;



    QWidget *up,*down;
    QVector<BtnToolTip *> *btn;

    QWidget *rBtnW;
    QHBoxLayout * rBtnL;
    Btn *btnEnter;
    BtnMnu *btnMenu;

    QWidget *leftWidg;
    QVBoxLayout *leftLayout;
    QPushButton *leftBtn;
    Btn *deleteBtn;
    Btn *bringbackBtn;
    QCheckBox *checkBox;

    QGridLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QToolBar * toolBar,*m_toolBarTwoo;
    QRect m_size;
    QWidget *leftBtnsWidg;
    QHBoxLayout *leftBtnsLayuot;

    void setObgectName();
    void showOll();
    void showOnlySlyders();
    void showOnlyOneSlyder();
    void checkBoxPosition();
public:
    void controlPosition();
    explicit Panel(QWidget *parent = nullptr);
    virtual ~Panel();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    int getWigthLine(){return this->slyderThickness->value();}
    int getColor(){return this->slyderColor->value();}
signals:
    void enterBtn();
    void changeColor(QColor color);
    void changeWidthLine(int value);
    void changeBtn(int btn);
    void hideLastFigure();
    void showLastFigure();
    void quitReader(bool isScreen = false);
    void savePicture();
    void copy();
    void checkBoxClicked(int isActive);
    void showToolTipP(QPoint pos,int index);
    void hideToolTipP();
public slots:
    void setcheckBox(bool isChecked);
    void changeFigure(int fig);
    void showHideDown();
    void checkBtns();
    void checkBtnsOk();
    void showInPosition(int x,int y,int x2,int y2,int width,int height);
    void changePosition(int x,int y,int x2,int y2,int width,int height);
    void setActiveRemoveBtn(bool isActive);
    void setActiveInsertBtn(bool isActive);
    void setWidth(int width);
};

#endif // PANEL_H
