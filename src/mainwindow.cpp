#include "inc/mainwindow.h"
#include <QApplication>
#include <QDesktopServices>
#include <QBuffer>
#include <QClipboard>
#include <QPropertyAnimation>
#include <QThread>
#include "inc/tabs/tray.h"
#include <QWidget>
#include <QEvent>


MainWindow::MainWindow(){
    m_graphicsEditor = nullptr;
    m_trayIcon = nullptr;
    m_menu = nullptr;
    m_timer = nullptr;
    m_key = nullptr;
    m_shortcutFullScrin = nullptr;
    m_shortcutPartScrin = nullptr;
    //m_wind = nullptr;
    m_tabRegist = new TabRegistration();
    connect(this->m_tabRegist,&TabRegistration::endOfRegistration,this,&MainWindow::programStart);
    m_tabRegist->connectServer();
    m_size = QApplication::screens().at(0)->geometry();
    m_btnForUrl = new BtnsForUrl(m_size.width()/8,m_size.height()/2 - m_size.height()/10);
    m_btnForUrl->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    m_btnForUrl->hide();
}

void MainWindow::programStart(){
    /*m_wind = new Wind();
    connect(m_wind,&Wind::enterPartOfScreen,this,&MainWindow::startGraphicsEditPart);
    connect(m_wind,&Wind::enterFullScrin,this,&MainWindow::startGraphicsEditFull);
    connect(m_wind,&Wind::enterHistory,this,&MainWindow::openHistory);*/
    connect(qApp,&QCoreApplication::aboutToQuit,this,&MainWindow::deleteUrl);
    m_trayIcon = new Tray(QIcon(":/res/pict//close.png"));
    m_menu = new Menu();
    m_trayIcon->setContextMenu(m_menu); 
    connect(m_menu,&Menu::enterPartOfScreen,this,&MainWindow::startGraphicsEditPart);
    connect(m_menu,&Menu::enterFullScrin,this,&MainWindow::startGraphicsEditFull);
    connect(m_menu,&Menu::enterHistory,this,&MainWindow::openHistory);
    connect(m_menu,&Menu::quit,this,&MainWindow::quit);
    connect(m_trayIcon, SIGNAL(leftMouseClick()), this, SLOT(startGraphicsEditPart()));
    m_trayIcon->show();
    #ifdef Q_OS_WIN32 || Q_OS_WIN
        m_key = HookKeybord::instance();
        m_key->startHook();
        connect(m_key,&HookKeybord::keyPress,this,&MainWindow::hoock);
    #else
    m_shortcutFullScrin = new QxtGlobalShortcut(this);
    m_shortcutFullScrin->setShortcut(QKeySequence("Ctrl+Shift+Print"));
    m_shortcutPartScrin = new QxtGlobalShortcut(this);
    m_shortcutPartScrin->setShortcut(QKeySequence("Print"));
    connect(m_shortcutFullScrin, &QxtGlobalShortcut::activated,this,&MainWindow::fullScreenHook);
    connect(m_shortcutPartScrin, &QxtGlobalShortcut::activated,this,&MainWindow::partScreenHook);
    show();
    hide();
    m_timer = new QTimer;
    m_timer->start(1000);
    connect(m_timer,&QTimer::timeout,this,&MainWindow::startHook);
    #endif
}
void MainWindow::quit(){
    qApp->quit();
}
void MainWindow::deleteUrl(){
    QFile in("QURL.dll");
    in.remove();
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

void MainWindow::openHistory(){
    QDesktopServices::openUrl(QUrl("http://vasilevka.ru/api/screenshots/history/"));
}
void MainWindow::startGraphicsEditFull(){
#ifdef Q_OS_WIN32 || Q_OS_WIN
    if(m_key)
        m_key->endHook();
#else
    m_shortcutFullScrin->setEnabled(false);
    m_shortcutPartScrin->setEnabled(false);
    m_timer->stop();
#endif
    m_graphicsEditor = new TabGraphicsEditor(true);
    connect(m_graphicsEditor,&TabGraphicsEditor::enterSavePixmap,this,&MainWindow::deleteGrapgicsEditor);
    connect(m_graphicsEditor,&TabGraphicsEditor::quitReader,this,&MainWindow::deleteGrapgicsEditor);
}
void MainWindow::startGraphicsEditPart(){
#ifdef Q_OS_WIN32 || Q_OS_WIN
    if(m_key)
        m_key->endHook();
#else
    m_shortcutFullScrin->setEnabled(false);
    m_shortcutPartScrin->setEnabled(false);
    m_timer->stop();
#endif

    m_graphicsEditor = new TabGraphicsEditor(false);
    connect(m_graphicsEditor,&TabGraphicsEditor::enterSavePixmap,this,&MainWindow::deleteGrapgicsEditor);
    connect(m_graphicsEditor,&TabGraphicsEditor::quitReader,this,&MainWindow::deleteGrapgicsEditor);
}
void MainWindow::deleteGrapgicsEditor(bool isScreen){
    if(m_graphicsEditor){
        m_graphicsEditor->hide();
        delete m_graphicsEditor;
        m_graphicsEditor = nullptr;
    }
    m_btnForUrl->move(m_size.width()-300,m_size.height()-300);
    m_btnForUrl->showVawe();
    if(!isScreen)
        m_btnForUrl->hide();
#ifdef Q_OS_WIN32 || Q_OS_WIN
    m_key->startHook();
#else
    m_shortcutFullScrin->setEnabled(true);
    m_shortcutPartScrin->setEnabled(true);
    m_timer->start();
#endif
}
void MainWindow::partScreenHook(){

    emit startGraphicsEditPart();
}
void MainWindow::fullScreenHook(){

    emit startGraphicsEditFull();
}
void MainWindow::startHook(){
#ifdef Q_OS_WIN32 || Q_OS_WIN
    m_key->startHook();
#else
    m_shortcutFullScrin->setShortcut(QKeySequence("Ctrl+Shift+Print"));
    m_shortcutPartScrin->setShortcut(QKeySequence("Print"));
#endif

}
void MainWindow::hoock(HookKeybord::HookKey hoo){
    if(!hoo){
        m_key->endHook();
        partScreenHook();
    }
    else if(hoo == 3){
        m_key->endHook();
        fullScreenHook();
    }
}
MainWindow::~MainWindow(){
    if(m_timer){
        m_timer->stop();
        delete m_timer;
        m_timer = nullptr;
    }
    if(m_shortcutFullScrin)
        delete m_shortcutFullScrin;
    if(m_shortcutPartScrin)
        delete m_shortcutPartScrin;
    if(m_key)
        delete m_key;

}
