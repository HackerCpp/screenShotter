#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


class Request : public QObject{
    Q_OBJECT
public:
    explicit Request(bool syn=true, QObject *parent = 0);
    void sendRequest(const QByteArray &method, const QByteArray &addr, QList <QByteArray> &headers, const QByteArray &body);
    void setParametersForRequetsSlot(const QByteArray &method, const QByteArray &addr, QList <QByteArray> &headers, const QByteArray &body);
    const QByteArray& getReply(){return replyBody;}

    QList<QByteArray> getReplyHeaders(){return replyHeaders;}
    int getError(){return replyError;}
    QString getErrorString(){return replyErrorString;}
    QString getReplyURL(){return replyURL;}
    void synchronous(bool s=true){synhro=s;}

private:
    QNetworkAccessManager *manager;
    QByteArray replyBody;
    QList<QByteArray> replyHeaders;
    bool ended;
    int replyError;
    QString replyErrorString;
    QString replyURL;
    bool synhro;

    QByteArray p_method;
    QByteArray p_addr;
    QList <QByteArray> p_headers;
    QByteArray p_body;

public slots:
    void sendRequest();

private slots:
    void sent(QNetworkReply *reply);

signals:
    void finished();
};

#endif // CLIENT_H
