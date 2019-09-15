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

class Wind : public QWidget{
     Q_OBJECT


    QSystemTrayIcon *trayIcon;
    QHBoxLayout *headerLayout;
    QLabel * headerLabelIcon,*headerLabelText;
    QPushButton * headerBtn;
    QVBoxLayout * mainVBoxLayout;
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
public slots:
    void hideWin();
    void showWin();
    void destroy();
};




class Panel : public QWidget
{
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

    QWidget * leftWidg;
    QVBoxLayout * leftLayout;
    QPushButton * leftBtn;

    QGridLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QToolBar * toolBar;

    QWidget *leftBtnsWidg;
    QHBoxLayout *leftBtnsLayuot;

    void setObgectName();
public:
    explicit Panel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void enterBtn();
    void changeColor(int value);
    void changeWidthLine(int value);
    void changeBtn(int btn);

public slots:
    void showHideDown();
    void checkBtns();
    void checkBtnsOk();
};

#endif // PANEL_H
