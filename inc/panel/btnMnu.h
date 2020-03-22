#ifndef BTNMNU_H
#define BTNMNU_H
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QString>
#include <QPolygon>

class BtnMnu : public QPushButton{
    Q_OBJECT
    int m_indent;
    virtual void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *e) override;
public:
    BtnMnu();
public slots:
    void showMenuT();

};

#endif // BTN_H
