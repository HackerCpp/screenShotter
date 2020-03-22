#ifndef DIALOGFORENTERPATHFORSAVESCREENSHOT_H
#define DIALOGFORENTERPATHFORSAVESCREENSHOT_H

#include "inc/tabs/tabbase.h"
#include <QLineEdit>
#include "inc/tabs/btnsokandcansel.h"
#include <QThread>
#include <QSettings>

class DialogForEnterPathForSaveScreenshot : public TabBase{
    Q_OBJECT
    QSettings m_settings;
    static DialogForEnterPathForSaveScreenshot *m_thisDialog;
    QVBoxLayout *m_vBoxLayout;
    QHBoxLayout *m_hBoxLayout;
    QLabel * m_label;
    QLineEdit * m_lineEdit;
    QPushButton *m_btnOpenDialog;
    BtnsOkAndCansel *m_btns;
    QString m_path;
    bool m_exec;
    explicit DialogForEnterPathForSaveScreenshot();
    virtual ~DialogForEnterPathForSaveScreenshot()override;
public:
    static DialogForEnterPathForSaveScreenshot* newsingleDialogForEnterPathForSaveScreenshot();
    QString getPath();



signals:

public slots:
    void openPath();
    void hideWin()override;
    void btnOK();
    void btnCansel();
};

#endif // DIALOGFORENTERPATHFORSAVESCREENSHOT_H
