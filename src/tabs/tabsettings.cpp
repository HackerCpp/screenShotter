#include "inc/tabs/tabsettings.h"
#include <QUrl>
#include "inc/settings/autoplay.h"
#include "ui_hotkey.h"


TabSettings::TabSettings(){
    setMinimumSize(500,500);
    m_btns = new BtnsOkAndCansel;

    m_tabWidget = new QTabWidget();
    m_tabSet = new SettingTab();
    m_tabWidget->addTab(m_tabSet,"Настройки");
    m_hotKeyWidget = new QWidget;
    Ui_HotKey hotKey;
    hotKey.setupUi(m_hotKeyWidget);
    m_tabWidget->addTab(m_hotKeyWidget,"Горячие клавиши");
    mainVBoxLayout->addWidget(m_tabWidget);
    mainVBoxLayout->addWidget(m_btns);
    m_tabWidget->tabBar()->setMinimumWidth(500);

    connect(m_btns,&BtnsOkAndCansel::btnOkEnter,this,&TabSettings::btnOkEnter);
    connect(m_btns,&BtnsOkAndCansel::btnCanselEnter,this,&TabSettings::btnCanselEnter);
}

void TabSettings::btnOkEnter(){
    AutoPlay autoPlay;
    autoPlay.setAutoPlay(m_tabSet->isAutoPlay());
    m_settings.setValue("/Settings/Base/pathForSave",m_tabSet->pathForSaveScreenShot());
    m_settings.setValue("/Settings/Base/isNameActiveWindow",m_tabSet->isNameActiveWindow());
    m_settings.setValue("/Settings/Base/isGetUrl",m_tabSet->isGetUrl());
    hide();
}

void TabSettings::btnCanselEnter(){
    hide();
}

TabSettings::~TabSettings(){
    if(m_hotKeyWidget){
        delete m_hotKeyWidget;
        m_hotKeyWidget = nullptr;
    }
    if(m_tabSet){
        delete m_tabSet;
        m_tabSet = nullptr;
    }
    if(m_btns){
        delete m_btns;
        m_btns = nullptr;
    }
    if(mainVBoxLayout){
        delete mainVBoxLayout;
        mainVBoxLayout = nullptr;
    }


}
