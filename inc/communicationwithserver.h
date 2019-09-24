#ifndef COMMUNICATIONWITHSERVER_H
#define COMMUNICATIONWITHSERVER_H

#include <QString>
#include "inc/client.h"

class CommunicationWithServer{
    Request *m_request;
public:
    CommunicationWithServer();
    bool registration(QByteArray email,QByteArray password,QByteArray phoneNumber);
    bool authorization(QByteArray email,QByteArray password);
    bool isEmail(QByteArray email);
    QString sendPicture(QString email,QString password,QByteArray pict,QString fileName);
    ~CommunicationWithServer();
};

#endif // COMMUNICATIONWITHSERVER_H
