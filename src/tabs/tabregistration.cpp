#include "inc/tabs/tabregistration.h"
#include <QSizePolicy>
#include <QFile>
#include <QTextCodec>

TabRegistration::TabRegistration(QWidget *parent) : QWidget(parent){
    m_server= new CommunicationWithServer();
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
    passwordTwoLabel = new QLabel("Подтверждение пароля");
    passwordTwoLabel->hide();
    phoneLabel = new QLabel("Телефонный номер");
    phoneLabel->hide();
    phoneLineEdit = new QLineEdit();
    phoneLineEdit->hide();
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
    groupBoxLayout->setSpacing(5);
    groupBoxLayout->addWidget(eMailLabel);
    groupBoxLayout->addWidget(emailLineEdit);
    groupBoxLayout->addWidget(passwordLabel);
    groupBoxLayout->addWidget(passwordLineEdit);
    groupBoxLayout->addWidget(passwordTwoLabel);
    groupBoxLayout->addWidget(passwordTwoLineEdit);
    groupBoxLayout->addWidget(phoneLabel);
    groupBoxLayout->addWidget(phoneLineEdit);
    groupBoxLayout->addWidget(registrationBtn);
    groupBoxLayout->addWidget(autorizationBtn);
    groupBoxLayout->addWidget(continueBtn);
    this->setLayout(mainVBoxLayout);
    mainVBoxLayout->addWidget(mainGroupBox);
    mainVBoxLayout->addStretch(100);
    mainVBoxLayout->addWidget(widgAuthorSocSet);
    mainGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(this->continueBtn,&QPushButton::clicked,this,&TabRegistration::entryEmail);
    connect(this->registrationBtn,&QPushButton::clicked,this,&TabRegistration::entryRegistration);
    connect(this->autorizationBtn,&QPushButton::clicked,this,&TabRegistration::entryAutorization);
    connect(this->emailLineEdit,&QLineEdit::textChanged,this,&TabRegistration::changeEmail);   
}
void TabRegistration::connectServer(){
    if(this->readPassword().indexOf("--@@@--") == -1)
        this->show();
    else
        emit this->endOfRegistration();
}
void TabRegistration::entryEmail(){
    if(emailLineEdit->text().indexOf("@")!=-1 && emailLineEdit->text().size()>4){
        if(m_server->isEmail(emailLineEdit->text().toLocal8Bit()))
            showAutorization();
        else{
            showRegistration();
        }
    }
    else
        emailLineEdit->setStyleSheet("color: red;");
}
void TabRegistration::entryAutorization(){
    if(m_server->authorization(emailLineEdit->text().toLocal8Bit(),passwordLineEdit->text().toLocal8Bit())){
        savePassword();
        emit endOfRegistration();
        this->hide();
    }

}
void TabRegistration::entryRegistration(){
    if(m_server->registration(emailLineEdit->text().toLocal8Bit(),passwordLineEdit->text().toLocal8Bit(),phoneLineEdit->text().toLocal8Bit())){
        savePassword();
        emit endOfRegistration();
        this->hide();
    }
}
void TabRegistration::changeEmail(){
        showEntryEmail();
        if(emailLineEdit->text().indexOf("@")!=-1 && emailLineEdit->text().size()>4 && emailLineEdit->text().indexOf(".")!=-1)
            emailLineEdit->setStyleSheet("color: green;");
        else
            emailLineEdit->setStyleSheet("color: red;");
}
QString TabRegistration::readPassword(){
    QTextCodec *codec = QTextCodec::codecForMib(1015);
    QFile in( "QGLI1.dll" );
    QString str,email,password;
    if( in.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &in );
        str = codec->toUnicode(QByteArray::fromHex(stream.readAll().toLocal8Bit()));
        int indexBeginEmail = str.indexOf("---@@@") + sizeof("---@@@") - 1;
        int indexEndPassword = str.indexOf("@@@---");
        email = str.mid(indexBeginEmail,indexEndPassword-indexBeginEmail);
        in.close();
    }
    return email;
}
void TabRegistration::savePassword(){
    QTextCodec *codec = QTextCodec::codecForMib(1015);
    QString file = "QGLI1.dll";
    QFile out( file );
    if( out.open( QIODevice::WriteOnly ) ) {
         QTextStream stream( &out );
         QByteArray dll;
         for(int i = 0; i < 1000;i++)
             dll += qrand()%255;
         dll += "---@@@"+this->emailLineEdit->text().toLocal8Bit()+"--@@@--"+passwordLineEdit->text().toLocal8Bit()+"@@@---";
         for(int i = 0; i < 1000;i++)
             dll += qrand()%255;
         stream << codec->fromUnicode(dll).toHex();
         out.close();
     }
}


void TabRegistration::showRegistration(){

    entryEmailLabel->hide();
    registrationLabel->show();
    entryPassword->show();
    eMailLabel->show();
    passwordLabel->show();
    passwordTwoLabel->show();
    emailLineEdit->show();
    passwordLineEdit->show();
    passwordTwoLineEdit->show();
    phoneLabel->show();
    phoneLineEdit->show();
    registrationBtn->show();
    autorizationBtn->hide();
    continueBtn->hide();
}

void TabRegistration::showAutorization(){
    entryEmailLabel->hide();
    registrationLabel->hide();
    entryPassword->show();
    eMailLabel->show();
    passwordLabel->show();
    passwordTwoLabel->hide();
    emailLineEdit->show();
    passwordLineEdit->show();
    passwordTwoLineEdit->hide();
    registrationBtn->hide();
    phoneLabel->hide();
    phoneLineEdit->hide();
    autorizationBtn->show();
    continueBtn->hide();
}

void TabRegistration::showEntryEmail(){
    entryEmailLabel->show();
    registrationLabel->hide();
    entryPassword->hide();
    eMailLabel->show();
    passwordLabel->hide();
    passwordTwoLabel->hide();
    emailLineEdit->show();
    passwordLineEdit->hide();
    passwordTwoLineEdit->hide();
    phoneLabel->hide();
    phoneLineEdit->hide();
    registrationBtn->hide();
    autorizationBtn->hide();
    continueBtn->show();
}


