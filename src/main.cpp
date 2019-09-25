#include "inc\mainwindow.h"
#include <QApplication>
#include <QFile>
#include "inc\panel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFile File("css\\style.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
    return a.exec();
}
