#include "inc/tabs/tabregistration.h"
#include <QSizePolicy>

TabRegistration::TabRegistration(QWidget *parent) : QWidget(parent){
    this->setFixedSize(400,400);
    widgAuthorSocSet = new QWidget();
    mainGroupBox = new QGroupBox;
    mainVBoxLayout = new QVBoxLayout;
    groupBoxLayout = new QVBoxLayout;
    entryEmailLabel = new QLabel("Для начала работы введите e-mail");
    registrationLabel = new QLabel("Регистрация");
    registrationLabel->hide();
    entryPassword = new QLabel("Введите пароль");
    entryPassword->hide();
    eMailLabel = new QLabel("E-mail");
    passwordLabel = new QLabel("Пароль");
    passwordLabel->hide();
    passwordTwoLabel = new QLabel("подтверждение пароля");
    passwordTwoLabel->hide();
    emailLineEdit = new QLineEdit();
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->hide();
    passwordTwoLineEdit = new QLineEdit();
    passwordTwoLineEdit->hide();
    registrationBtn = new QPushButton("Регистрация");
    registrationBtn->hide();
    registrationBtn->setFixedWidth(100);
    autorizationBtn = new QPushButton("Авторизация");
    autorizationBtn->hide();
    autorizationBtn->setFixedWidth(100);
    continueBtn = new QPushButton("Далее");
    continueBtn->setFixedWidth(100);
    mainGroupBox->setLayout(groupBoxLayout);
    groupBoxLayout->addWidget(entryEmailLabel);
    groupBoxLayout->addWidget(registrationLabel);
    groupBoxLayout->addWidget(entryPassword);
    groupBoxLayout->setSpacing(20);
    groupBoxLayout->addWidget(eMailLabel);
    groupBoxLayout->addWidget(emailLineEdit);
    groupBoxLayout->addWidget(passwordLabel);
    groupBoxLayout->addWidget(passwordLineEdit);
    groupBoxLayout->addWidget(passwordTwoLabel);
    groupBoxLayout->addWidget(passwordTwoLineEdit);
    groupBoxLayout->addWidget(registrationBtn);
    groupBoxLayout->addWidget(autorizationBtn);
    groupBoxLayout->addWidget(continueBtn);
    this->setLayout(mainVBoxLayout);
    mainVBoxLayout->addWidget(mainGroupBox);
    mainVBoxLayout->addStretch(1000);
    mainVBoxLayout->addWidget(widgAuthorSocSet);
    mainGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}
