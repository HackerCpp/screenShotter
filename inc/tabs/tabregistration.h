#ifndef TBAREGISTRATION_H
#define TBAREGISTRATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>

class TabRegistration : public QWidget{
    Q_OBJECT
    QGroupBox * mainGroupBox;
    QVBoxLayout *mainVBoxLayout,*groupBoxLayout;
    QLabel * entryEmailLabel,*registrationLabel,*entryPassword,
    *eMailLabel,*passwordLabel,*passwordTwoLabel;
    QLineEdit * emailLineEdit,*passwordLineEdit,*passwordTwoLineEdit;
    QPushButton * registrationBtn,*autorizationBtn,*continueBtn;
    QWidget * widgAuthorSocSet;
public:
    explicit TabRegistration(QWidget *parent = nullptr);
    void showRegistration();
    void showAutorization();
    void showEntryEmail();

signals:

public slots:
};

#endif // TBAREGISTRATION_H
