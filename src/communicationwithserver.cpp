#include "inc/communicationwithserver.h"
#include <QCoreApplication>

CommunicationWithServer::CommunicationWithServer(){
    m_request = new Request();
}
bool CommunicationWithServer::registration(QByteArray email,QByteArray password,QByteArray phoneNumber){
    QList<QByteArray> header;
    header.append("Content-Type: application/x-www-form-urlencoded");
    m_request->setParametersForRequetsSlot("POST","http://vasilevka.ru/api/users/add/",header,
      "email="+email+"&password="+password+"&phone="+phoneNumber);
    m_request->sendRequest();
    QTime time;
    time.start();
    while(m_request->getReply().isEmpty() && time.elapsed() < 2000){
        qApp->processEvents();
    }
    QByteArray reply = m_request->getReply();
    QByteArray result = reply.mid(reply.indexOf("\"result\":") + sizeof("\"result\":"),2);
    return result == "ok"?true:false;
}
bool CommunicationWithServer::authorization(QByteArray email,QByteArray password){
    QList<QByteArray> header;
    header.append("Content-Type: application/x-www-form-urlencoded");
    m_request->setParametersForRequetsSlot("POST","http://vasilevka.ru/api/users/check/",header,
      "email="+email+"&password="+password);
    m_request->sendRequest();
    QTime time;
    time.start();
    while(m_request->getReply().isEmpty() && time.elapsed() < 2000){
        qApp->processEvents();
    }
    QByteArray reply = m_request->getReply();
    QByteArray result = reply.mid(reply.indexOf("\"result\":") + sizeof("\"result\":"),2);
    return result == "ok"?true:false;
}
bool CommunicationWithServer::isEmail(QByteArray email){
    QList<QByteArray> header;
    header.append("Content-Type: application/x-www-form-urlencoded");
    m_request->setParametersForRequetsSlot("POST","http://vasilevka.ru/api/users/check/",header,
      "email="+email+"&action=searchuser");
    m_request->sendRequest();
    QTime time;
    time.start();
    while(m_request->getReply().isEmpty() && time.elapsed() < 2000){
        qApp->processEvents();
    }
    QByteArray reply = m_request->getReply();
    return reply.indexOf("User not found") == -1?true:false;
}
QString CommunicationWithServer::sendPicture(QString email,QString password,QByteArray pict,QString fileName){
    QString bound="margin";
    QByteArray data = ("--margin\r\n");
    data.append("Content-Disposition: form-data; name=\"email\"\r\n\r\n");
    data.append( email+"\r\n");
    data.append("--" + bound +"\r\n");
    data.append("Content-Disposition: form-data; name=\"password\"\r\n\r\n");
    data.append(password+"\r\n");
    data.append("--" + bound + "\r\n");
    data.append("Content-Disposition: form-data; name=\"url\"\r\n\r\n");
    data.append("url\r\n");
    data.append("--" + bound + "\r\n");
    data.append("Content-Disposition: form-data; name=\"screenshot\"; filename=\""+fileName+"\"\r\n");
    QString fileFormat = fileName.mid(fileName.indexOf(".")+1);
    data.append("Content-Type: image/"+fileFormat+"\r\n\r\n");
    data.append(pict);
    data.append("\r\n");
    data.append("--margin--\r\n");
    QList<QByteArray> *headers = new QList<QByteArray>;
    headers->append("Content-Length:");
    headers->append(QString::number(data.length()).toUtf8());
    headers->append("Content-Type: multipart/form-data; boundary=margin");
    headers->append("DNT: 1");
    headers->append("Host: vasilevka.ru");
    m_request->setParametersForRequetsSlot("POST","http://vasilevka.ru/api/screenshots/upload/",*headers,data);
    m_request->sendRequest();
    QTime time;
    time.start();
    while(m_request->getReply().isEmpty() && time.elapsed() < 1000){
        qApp->processEvents();
    }
    QByteArray reply = m_request->getReply();
    QByteArray result = reply.mid(reply.indexOf("\"result\":") + sizeof("\"result\":"),2);
    if(result == "ok"){
        int indexBeginUrl = reply.indexOf("\"url\":\"")+sizeof ("\"url\":\"")-1;
        int sizeUrl = reply.indexOf(",",indexBeginUrl) - indexBeginUrl -1;
        QByteArray url = reply.mid(indexBeginUrl,sizeUrl);
        return url;
    }
    else {
        return nullptr;
    }
}
CommunicationWithServer::~CommunicationWithServer(){
    if(this->m_request)
        delete m_request;
    m_request = nullptr;
}
