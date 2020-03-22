#ifndef BTNSOKANDCANSEL_H
#define BTNSOKANDCANSEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class BtnsOkAndCansel : public QWidget{
    Q_OBJECT

    QHBoxLayout *m_layoutForBtns;
    QPushButton *m_btnCansel,*m_btnOk;

    void setName();
public:
    BtnsOkAndCansel();
    ~BtnsOkAndCansel();
signals:
   void btnOkEnter();
   void btnCanselEnter();
};

#endif // BTNSOKANDCANSEL_H
