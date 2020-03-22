#include "inc/tabs/btnsokandcansel.h"

void BtnsOkAndCansel::setName(){
    this->setObjectName("settingsBtns");
    m_btnCansel->setObjectName("settingsBtnCansel");
}

BtnsOkAndCansel::BtnsOkAndCansel(){
    m_btnOk = new QPushButton("Применить");
    m_layoutForBtns = new QHBoxLayout;
    m_btnCansel = new QPushButton("Отменить");
    m_layoutForBtns->addStretch(1000);
    m_layoutForBtns->addWidget(m_btnCansel);
    m_layoutForBtns->addWidget(m_btnOk);
    m_layoutForBtns = new QHBoxLayout;
    m_btnCansel = new QPushButton("Отменить");
    m_layoutForBtns->addStretch(1000);
    m_layoutForBtns->addWidget(m_btnCansel);
    m_layoutForBtns->addWidget(m_btnOk);
    this->setLayout(m_layoutForBtns);

    connect(m_btnOk,&QPushButton::clicked,this,&BtnsOkAndCansel::btnOkEnter);
    connect(m_btnCansel,&QPushButton::clicked,this,&BtnsOkAndCansel::btnCanselEnter);
}

BtnsOkAndCansel::~BtnsOkAndCansel(){
    if(m_btnOk){
        delete m_btnOk;
        m_btnOk = nullptr;
    }
    if(m_btnCansel){
        delete m_btnCansel;
        m_btnCansel = nullptr;
    }
    if(m_layoutForBtns){
        delete m_layoutForBtns;
        m_layoutForBtns = nullptr;
    }
}
