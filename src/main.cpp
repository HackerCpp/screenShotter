#include "inc\mainwindow.h"
#include <QApplication>
#include <QFile>
#include "inc\panel.h"
#include "inc/client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    QList<QByteArray> *headers = new QList<QByteArray>;
    headers->append("");
    Request *request = new Request();
    QFile file("D:\\Project\\ScreenShot\\screenShot\\screenShot\\pict\\x2.png");
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "file not open";
    /*request->setParametersForRequetsSlot("POST",
                                         "http://vasilevka.ru/api/users/add/"
                                         ,*headers,
      "email=s@mail.ru&password=passworg&phone=224455");
    request->setParametersForRequetsSlot("POST","http://vasilevka.ru/api/users/check/",*headers,
      "email=s@mail.ru&password=passworg");*/
    QByteArray fileR = file.readAll();
    //qDebug() << fileR;
    request->setParametersForRequetsSlot("POST","http://vasilevka.ru/api/screenshots/upload/",*headers,
      "email=s@mail.ru&password=passworg&url=\
http://vasilevka.ru/api/screenshots/upload/f&screenshot="+fileR);
    request->sendRequest();
    QFile File("css\\style.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
    return a.exec();
}
