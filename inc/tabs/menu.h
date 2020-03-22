#ifndef MENU_H
#define MENU_H
#include <QMenu>
#include "inc/hookkeybord.h"
#include "qxtglobalshortcut.h"
#include "inc/tabs/tabsettings.h"

class Menu : public QMenu{
    Q_OBJECT
    TabSettings *m_settings;
public:
    Menu();
    virtual ~Menu();
signals:
   void enterPartOfScreen();
   void enterFullScrin();
   void enterHistory();
   void quit();
public slots:
   void enterSetting();

};

#endif // MENU_H
