#ifndef BTN_H
#define BTN_H
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QString>

class Btn : public QPushButton{
    Q_OBJECT
    virtual void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *e) override;
public:
    Btn();
signals:
    void rightClick();
};

#endif // BTN_H
