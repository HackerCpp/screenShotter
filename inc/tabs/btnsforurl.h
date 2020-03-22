#ifndef BTNSFORURL_H
#define BTNSFORURL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QTimer>

class BtnsForUrl : public QGroupBox{
    Q_OBJECT
    QTimer *m_timer;
    QHBoxLayout * m_hBoxLayout;
    QPushButton * m_pushBtn[2];
    int m_width,m_height;
public:
    BtnsForUrl(int widthParent,int heightParent,QWidget* parent = Q_NULLPTR);
    void showVawe();
    bool isFileExist();
protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
public slots:
    void updateTimer();
    void openUrl();
    void copyUrl();

};

#endif // BTNSFORURL_H
