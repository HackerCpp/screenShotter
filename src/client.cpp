#include "inc/client.h"
#include <QCoreApplication>
#include <QDebug>

Request::Request(bool syn, QObject *parent) :
    QObject(parent),synhro(syn){
    manager=new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sent(QNetworkReply*)));
}

void Request::setParametersForRequetsSlot(const QByteArray &method, const QByteArray &addr, QList<QByteArray> &headers, const QByteArray &body){
    p_method=method;
    p_addr=addr;
    p_headers=headers;
    p_body=body;
}

void Request::sendRequest(){
    sendRequest(p_method, p_addr, p_headers, p_body);
}

void Request::sendRequest(const QByteArray &method, const QByteArray &addr, QList<QByteArray> &headers, const QByteArray &body){
    int type=0;
    QByteArray ba=method.simplified().toLower();
    if(ba.contains("put"))type=1;
    else if(ba.contains("get"))type=2;
    //post - default

    QNetworkRequest request;
    for(int i=0;i<headers.count();i++){
        ba=headers.at(i);
        int x=ba.indexOf(": ");
        if(x<0)continue;//игнорирование неверной строчки
        if(x==ba.length()-2)continue;
        request.setRawHeader(ba.left(x),ba.right(ba.length()-x-2));
    }
    if(type!=2) request.setHeader(QNetworkRequest::ContentLengthHeader, body.length()); //не гет
    request.setUrl(QUrl(addr));

    replyBody.clear();
    replyHeaders.clear();
    ended=false;

    switch(type){
    case 0: manager->post(request,body);
        break;
    case 1: manager->put(request, body);
        break;
    case 2: manager->get(request);
    }

    //подождать
    if(synhro) while(!ended)QCoreApplication::processEvents();
}

void Request::sent(QNetworkReply *reply){
    replyBody=reply->readAll();
    qDebug() << replyBody;
    replyHeaders=reply->rawHeaderList();
    for(int i=0;i<replyHeaders.count();i++){
        replyHeaders[i]=replyHeaders.at(i)+": "+reply->rawHeader(replyHeaders.at(i));
    }
    replyError=reply->error();
    replyErrorString=reply->errorString();
    replyURL=reply->url().toString();
    ended=true;
    emit finished();
}
