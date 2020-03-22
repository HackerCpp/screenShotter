#include "inc/mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QLibraryInfo>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("kwork");
    QCoreApplication::setApplicationName("screenShotter");
    QApplication::setQuitOnLastWindowClosed(false);
    MainWindow w;
    QFile File(":/res/css/style.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
    return a.exec();
}
