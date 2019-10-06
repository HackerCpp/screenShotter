#ifndef MEN_H
#define MEN_H

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





class Panel : public QWidget{
    Q_OBJECT

    int thisWidth,thisHeight;
    QPushButton *prevBtnInd;
    QPoint previousPoint;
    bool showDown;
    bool active;
    QSlider *slyderColor,*slyderThickness;
    QHBoxLayout * slydersLayout;


    QWidget *up,*down;
    QVector<QPushButton *> *btn;

    QWidget *rBtnW;
    QHBoxLayout * rBtnL;
    QPushButton *btnEnter;
    QPushButton *btnMenu;

    QWidget *leftWidg;
    QVBoxLayout *leftLayout;
    QPushButton *leftBtn;
    QPushButton *deleteBtn;
    QPushButton *bringbackBtn;

    QGridLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QToolBar * toolBar;
    QRect m_size;
    QWidget *leftBtnsWidg;
    QHBoxLayout *leftBtnsLayuot;

    void setObgectName();

public:
    void controlPosition();
    explicit Panel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int getWigthLine(){return this->slyderThickness->value();}
    int getColor(){return this->slyderColor->value();}
signals:
    void enterBtn();
    void changeColor(int value);
    void changeWidthLine(int value);
    void changeBtn(int btn);
    void hideLastFigure();
    void showLastFigure();

public slots:
    void showHideDown();
    void checkBtns();
    void checkBtnsOk();
};

#endif // PANEL_H
