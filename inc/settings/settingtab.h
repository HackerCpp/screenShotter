#ifndef SETTINGTAB_H
#define SETTINGTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QSettings>

class SettingTab : public QWidget{
    Q_OBJECT
    QSettings m_settings;
    QComboBox *m_comboLan;
    QLabel *m_labelFunc, *m_labelLangvich;
    QVBoxLayout *m_mainLayout;
    QCheckBox *m_checkBox[7];
    QString m_pathForSaveScreenShot;
public:
    bool isAutoPlay();
    bool isNameActiveWindow();
    bool isGetUrl();
    QString pathForSaveScreenShot();
    SettingTab();
public slots:
    void setPathForSaveScreenshot(int state);
};

#endif // SETTINGTAB_H
