#include "inc/settings/settingtab.h"
#include "inc/tabs/dialogforenterpathforsavescreenshot.h"
#include <QDebug>

SettingTab::SettingTab(){
    m_labelFunc = new QLabel("Функционал");
    m_labelLangvich = new QLabel("Язык");
    m_mainLayout = new QVBoxLayout;
    m_comboLan = new QComboBox;
    m_checkBox[0] = new QCheckBox("Запускать программу при старте системы");
    m_checkBox[1] = new QCheckBox("Сохранять копию скриншота в выбранную папку");
    m_checkBox[2] = new QCheckBox("Отображать процесс загрузки на сервер");
    m_checkBox[3] = new QCheckBox("После окончания загрузки выводить информационное окно");
    m_checkBox[4] = new QCheckBox("Использовать в имени скриншота название активного окна");
    m_checkBox[5] = new QCheckBox("Получать прямую ссылку на скриншот или файл");
    m_checkBox[6] = new QCheckBox("Показывать лупу ");
    m_mainLayout->setMargin(0);
    m_mainLayout->addSpacing(27);
    m_mainLayout->addWidget(m_labelFunc);
    for(int i = 0; i < 7;++i){
        m_mainLayout->addSpacing(18);
        m_mainLayout->addWidget(m_checkBox[i]);
    }
    m_mainLayout->addSpacing(27);
    m_mainLayout->addWidget(m_labelLangvich);
    m_mainLayout->addWidget(m_comboLan);
    setLayout(m_mainLayout);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QComboBox{max-width:90px;\
                             min-height:25px;\
                             margin-left: 38px;}\
QLabel{background-color: rgba(0, 0, 0, 0.0);\
                  font-family: Times New Roman;\
                  font-size: 25px;\
                  font-weight:600;\
                  color:black;margin-left: 32px;}\
                  QCheckBox{background-color: rgba(0, 0, 0, 0.0);\
                            font-family: Arial;\
                                font-size: 8pt;\
              color:black;margin-left: 38px;}\
              QCheckBox::indicator::unchecked{\
              background-color: rgba(255, 255, 255, 1);\
              border:2px solid black;\
              border-radius:3px;}\
              QCheckBox::indicator::checked{\
              background-color: rgba(0, 0, 0, 1);\
              border:2px solid black;border-radius:3px;}");
    m_checkBox[0]->setChecked(m_settings.value("/Settings/Base/autoPlay").toBool());
    QString m_path = m_settings.value("/Settings/Base/pathForSave").toString();
    m_checkBox[1]->setChecked(!m_path.isEmpty());
    m_checkBox[4]->setChecked(m_settings.value("/Settings/Base/isNameActiveWindow").toBool());
    m_checkBox[5]->setChecked(m_settings.value("/Settings/Base/isGetUrl").toBool());
    connect(this->m_checkBox[1],&QCheckBox::stateChanged,this,&SettingTab::setPathForSaveScreenshot);
}

bool SettingTab::isAutoPlay(){
     return m_checkBox[0]->isChecked();
}
bool SettingTab::isNameActiveWindow(){
    return m_checkBox[4]->isChecked();
}
bool SettingTab::isGetUrl(){
    return m_checkBox[5]->isChecked();
}
QString SettingTab::pathForSaveScreenShot(){
    return m_pathForSaveScreenShot;
}

void SettingTab::setPathForSaveScreenshot(int state){
    if(state == 2){
        DialogForEnterPathForSaveScreenshot *dialog = DialogForEnterPathForSaveScreenshot::newsingleDialogForEnterPathForSaveScreenshot();
        m_pathForSaveScreenShot = dialog->getPath();
        m_checkBox[1]->setCheckState(m_pathForSaveScreenShot.isEmpty()?Qt::Unchecked:Qt::Checked);
    }
    else if(!state){
        m_pathForSaveScreenShot = nullptr;
    }
}



