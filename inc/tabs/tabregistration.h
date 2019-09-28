#ifndef TBAREGISTRATION_H
#define TBAREGISTRATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include "inc/communicationwithserver.h"

class TabRegistration : public QWidget{
    Q_OBJECT
    CommunicationWithServer * m_server;
    QGroupBox * mainGroupBox;
    QVBoxLayout *mainVBoxLayout,*groupBoxLayout;
    QLabel * entryEmailLabel,*registrationLabel,*entryPassword,
    *eMailLabel,*passwordLabel,*passwordTwoLabel,*phoneLabel;
    QLineEdit * emailLineEdit,*passwordLineEdit,*passwordTwoLineEdit,*phoneLineEdit;
    QPushButton * registrationBtn,*autorizationBtn,*continueBtn;
    QWidget * widgAuthorSocSet;
public:
    explicit TabRegistration(QWidget *parent = nullptr);
    void showRegistration();
    void showAutorization();
    void showEntryEmail();
    QString readPassword();
    void connectServer();

signals:
    void endOfRegistration();

public slots:
    void savePassword();
    void entryEmail();
    void entryAutorization();
    void entryRegistration();
    void changeEmail();
};

#endif // TBAREGISTRATION_H
