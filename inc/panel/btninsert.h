#ifndef BTNINSERT_H
#define BTNINSERT_H
#include "inc/panel/btn.h"

class BtnInsert : public Btn{
    void paintEvent(QPaintEvent *event)override;
public:
    BtnInsert();

};

#endif // BTNINSERT_H
