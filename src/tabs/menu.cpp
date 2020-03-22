#include "inc/tabs/menu.h"
#include <QDebug>

Menu::Menu(){
    m_settings = new TabSettings();
    addAction("Снимок фрагмента экрана", this,&Menu::enterPartOfScreen);
    addAction("Снимок экрана", this,&Menu::enterFullScrin);
    addSeparator();
    addAction("Настройки", this,&Menu::enterSetting);
    addAction("История", this,&Menu::enterHistory);
    addSeparator();
    addAction( new QAction(tr("Открыть последнюю ссылку"), this));
    addAction( new QAction(tr("Скопировать последнюю ссылку"), this));
    addSeparator();
    addAction( new QAction(tr("Помощь"), this));
    addAction("Выход", this,&Menu::quit);
    //setAttribute(Qt::WA_TranslucentBackground);
    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    //setStyleSheet("background-color: rgba(255, 255, 255, 1);color:#000000;");

}
void Menu::enterSetting(){
    m_settings->show();
}

Menu::~Menu(){
    if(m_settings){
        delete m_settings;
        m_settings = nullptr;
    }
}
