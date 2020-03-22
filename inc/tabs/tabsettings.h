#ifndef TABSETTINGS_H
#define TABSETTINGS_H

#include "inc/tabs/tabbase.h"
#include "inc/settings/settingtab.h"
#include <QTabWidget>
#include "inc/tabs/btnsokandcansel.h"
#include <QSettings>

class TabSettings : public TabBase{
    Q_OBJECT
    QSettings m_settings;
    QTabWidget *m_tabWidget;
    SettingTab * m_tabSet;
    QWidget *m_hotKeyWidget;
    BtnsOkAndCansel *m_btns;

public:
    explicit TabSettings();
    virtual ~TabSettings();
signals:
public slots:
    void btnOkEnter();
    void btnCanselEnter();
};

#endif // TABSETTINGS_H
