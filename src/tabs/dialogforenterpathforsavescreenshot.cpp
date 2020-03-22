#include "inc/tabs/dialogforenterpathforsavescreenshot.h"
#include <QFileDialog>
#include <QDebug>
#include <QApplication>

DialogForEnterPathForSaveScreenshot * DialogForEnterPathForSaveScreenshot::m_thisDialog = nullptr;
DialogForEnterPathForSaveScreenshot::DialogForEnterPathForSaveScreenshot(){
    m_thisDialog = this;
    setMinimumSize(500,200);
    m_exec = true;
    m_vBoxLayout = new QVBoxLayout;
    m_hBoxLayout = new QHBoxLayout;
    m_vBoxLayout->setMargin(2);
    m_btnOpenDialog = new QPushButton("...");
    m_label = new QLabel("Выберите путь для сохранения скриншота");
    m_lineEdit = new QLineEdit;
    m_hBoxLayout->addWidget(m_lineEdit);
    m_hBoxLayout->addWidget(m_btnOpenDialog);
    m_vBoxLayout->addWidget(m_label);
    m_vBoxLayout->addLayout(m_hBoxLayout);
    m_btns = new BtnsOkAndCansel;

    this->mainVBoxLayout->addLayout(m_vBoxLayout);
    this->mainVBoxLayout->addWidget(m_btns);
    connect(m_btnOpenDialog,&QPushButton::clicked,this,&DialogForEnterPathForSaveScreenshot::openPath);
    connect(m_btns,&BtnsOkAndCansel::btnOkEnter,this,&DialogForEnterPathForSaveScreenshot::btnOK);
    connect(m_btns,&BtnsOkAndCansel::btnCanselEnter,this,&DialogForEnterPathForSaveScreenshot::btnCansel);
    m_lineEdit->setText(m_settings.value("/Settings/Base/pathForSave").toString());
}


QString DialogForEnterPathForSaveScreenshot::getPath(){
    this->show();
    while(m_exec){
        QApplication::processEvents();
    }
    this->deleteLater();
    return m_lineEdit->text();
}
DialogForEnterPathForSaveScreenshot* DialogForEnterPathForSaveScreenshot::newsingleDialogForEnterPathForSaveScreenshot(){
    if(m_thisDialog)
        return m_thisDialog;
    return new DialogForEnterPathForSaveScreenshot();
}
void DialogForEnterPathForSaveScreenshot::btnOK(){
    m_exec = false;
}
void DialogForEnterPathForSaveScreenshot::btnCansel(){
    m_lineEdit->setText("");
    m_exec = false;
}
void DialogForEnterPathForSaveScreenshot::hideWin(){
    btnCansel();
}
void DialogForEnterPathForSaveScreenshot::openPath(){
    QFileDialog *fileD = new QFileDialog(this);
    fileD->setAttribute(Qt::WA_QuitOnClose,false);
    m_lineEdit->setText(fileD->getExistingDirectory(this->parentWidget(),"",""));
}
DialogForEnterPathForSaveScreenshot::~DialogForEnterPathForSaveScreenshot(){
    m_thisDialog = nullptr;
    delete m_lineEdit;
    delete m_btnOpenDialog;
    delete m_label;
    delete m_hBoxLayout;
    delete m_vBoxLayout;
}
