#include "inc/mainwindow.h"
#include <QApplication>
#include <QDesktopServices>
#include <QBuffer>
#include <QClipboard>

MainWindow::MainWindow(){
    m_graphicsEditor = nullptr;
    m_wind = nullptr;
    m_tabRegist = new TabRegistration();
    connect(this->m_tabRegist,&TabRegistration::endOfRegistration,this,&MainWindow::programStart);
    m_tabRegist->connectServer();
}

void MainWindow::programStart(){
    m_wind = new Wind();
    connect(m_wind,&Wind::enterPartOfScreen,this,&MainWindow::startGraphicsEditPart);
    connect(m_wind,&Wind::enterFullScrin,this,&MainWindow::startGraphicsEditFull);
    connect(m_wind,&Wind::enterOpen,this,&MainWindow::openUrl);
    connect(m_wind,&Wind::enterCopy,this,&MainWindow::copyUrl);
}
QUrl getCurentUrl(){
    QFile in( "QURL.dll" );
    QUrl url;
    if( in.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &in );
        url = stream.readAll().remove("\\");
        in.close();
    }
    return url;
}
void MainWindow::openUrl(){
    QDesktopServices::openUrl(getCurentUrl());
}
void MainWindow::copyUrl(){
    QUrl url = getCurentUrl();
    QString stringUrl =  url.toEncoded();
    QApplication::clipboard()->setText(stringUrl);
}
void MainWindow::startGraphicsEditFull(){
    m_wind->hide();
    m_graphicsEditor = new TabGraphicsEditor(true);
    connect(m_graphicsEditor,&TabGraphicsEditor::enterSavePixmap,this,&MainWindow::deleteGrapgicsEditor);
}
void MainWindow::startGraphicsEditPart(){
    m_wind->hide();
    m_graphicsEditor = new TabGraphicsEditor(false);
    connect(m_graphicsEditor,&TabGraphicsEditor::enterSavePixmap,this,&MainWindow::deleteGrapgicsEditor);
}
void MainWindow::deleteGrapgicsEditor(){
    if(m_graphicsEditor)
        delete m_graphicsEditor;
    m_wind->show();
}
MainWindow::~MainWindow(){

}
