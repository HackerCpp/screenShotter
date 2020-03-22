#include "inc/tabs/tabgraphicseditor.h"
#include <QMessageBox>
#include <QEvent>
#include <QFileDialog>
#include <QPixmap>
#include <QApplication>
#include <QClipboard>


TabGraphicsEditor::TabGraphicsEditor(bool isFullScreen,QWidget *parent)
    : QWidget(parent){
    m_settings = new QSettings;
    m_curentToolTip = nullptr;
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    m_graphicsWiev = new QGraphicsView(this);
    m_vBoxLayout = new QVBoxLayout();
    m_panel = new Panel(this);
    m_toolTips = new QVector<ToolTip*>(11);
    for(int i = 0; i < 11;i++){
        m_toolTips->data()[i] = new ToolTip(this);
        m_toolTips->data()[i]->setFixedSize(150,50);
    }
    m_panel->hide();
    m_scene = new ScreenScene(isFullScreen);
    m_graphicsWiev->setScene(m_scene);
    m_graphicsWiev->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    m_graphicsWiev->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->cursor().setPos(m_scene->width()/2,m_scene->height()/2);
    this->setLayout(m_vBoxLayout);
    m_vBoxLayout->setMargin(0);
    m_vBoxLayout->addWidget(m_graphicsWiev);
    this->showFullScreen();
    //this->move(-1,-1);
    //this->setFixedSize(m_graphicsWiev->width()+2,m_graphicsWiev->height()+2);
    if(isFullScreen)
        m_panel->showInPosition(width(),height(),width(),height(),width(),height());
    //this->show();
    connect(m_scene,&ScreenScene::showPanel,m_panel,&Panel::showInPosition);
    connect(m_scene,&ScreenScene::changeWidthL,m_panel,&Panel::setWidth);
    connect(m_scene,&ScreenScene::movePanel,m_panel,&Panel::changePosition);
    connect(m_scene,SIGNAL(savePicture(QPixmap*)),this,SLOT(savePicture(QPixmap*)));
    connect(m_scene,SIGNAL(enterSavePixmap()),this,SIGNAL(enterSavePixmap()));
    connect(this->m_panel,SIGNAL(quitReader()),this,SIGNAL(quitReader()));
    connect(this->m_panel,SIGNAL(changeColor(QColor)),this->m_scene,SLOT(changeColor(QColor)));

    connect(m_scene,SIGNAL(insertBtn(bool)),m_panel,SLOT(setActiveInsertBtn(bool)));
    connect(m_scene,SIGNAL(removeBtn(bool)),m_panel,SLOT(setActiveRemoveBtn(bool)));
    connect(this->m_panel,SIGNAL(changeWidthLine(int)),this->m_scene,SLOT(changeWLine(int)));
    connect(this->m_panel,SIGNAL(showToolTipP(QPoint,int)),this,SLOT(showToolTip(QPoint,int)));
    connect(this->m_panel,SIGNAL(hideToolTipP()),this,SLOT(hideToolTip()));
    connect(this->m_panel,SIGNAL(changeBtn(int)),this->m_scene,SLOT(changefigure(int)));
    connect(this->m_panel,SIGNAL(enterBtn()),this->m_scene,SLOT(savePixMap()));
    connect(this->m_panel,SIGNAL(hideLastFigure()),this->m_scene,SLOT(hideLastFigure()));
    connect(this->m_panel,SIGNAL(showLastFigure()),this->m_scene,SLOT(showLastFigure()));
    connect(this->m_panel,SIGNAL(savePicture()),this->m_scene,SLOT(savePicture()));
    connect(this->m_panel,SIGNAL(copy()),this->m_scene,SLOT(copyPicture()));
    connect(this->m_panel,SIGNAL(checkBoxClicked(int)),this->m_scene,SLOT(checkBoxClicked(int)));
    connect(this->m_scene,SIGNAL(copyPixMap()),this,SIGNAL(quitReader()));
    connect(this->m_scene,SIGNAL(activeFigure(int)),m_panel,SLOT(changeFigure(int)));
    connect(this->m_scene,SIGNAL(activeText(bool)),this->m_panel,SLOT(setcheckBox(bool)));
    m_scene->changefigure(m_settings->value("/Settings/Panel/Btn").toInt() + 1);
    QVariant close =  m_settings->value("/Settings/Editor/closeMessage");
    if(close.isNull())
        m_isMessag = true;
    else
        m_isMessag = close.toBool();
}
void TabGraphicsEditor::showToolTip(QPoint point,int index){
    m_toolTips->data()[index]->move(point);
    m_toolTips->data()[index]->show();
    m_curentToolTip = m_toolTips->data()[index];
}
void TabGraphicsEditor::hideToolTip(){
    if(!m_curentToolTip)
        return;
    m_curentToolTip->hide();
    m_curentToolTip = nullptr;
}
void TabGraphicsEditor::savePicture(QPixmap *pict){
    this->hide();
    QFileDialog *fileD = new QFileDialog(this->parentWidget());
    fileD->setAttribute(Qt::WA_QuitOnClose,false);
    QString fileName = fileD->getSaveFileName(this->parentWidget(),"Сохранить изображение","","PNG Image (*.png);;JPEG Image (*.jpg)");
    if(!fileName.isEmpty()){
        if(pict->save(fileName)){
            if(m_settings->value("/Settings/Base/isGetUrl").toBool())
                QApplication::clipboard()->setText(fileName);
        }
    }

    fileD->deleteLater();
    emit quitReader(false);
}
void TabGraphicsEditor::keyPressEvent(QKeyEvent *event) {
    m_scene->keyPressEvent(event);
    int key = event->key();
    switch(key){
    case Qt::Key_Escape:{
        if(m_isMessag){
            /*QMessageBox::StandardButton reply;
            QMessageBox  *ques = new QMessageBox(QMessageBox::NoIcon, "","Скриншот будет потерян! Вы действительно хотите закрыть редактор?",QMessageBox::Yes | QMessageBox::No);
            ques->setWindowFlags(Qt::WindowStaysOnTopHint);
            reply = ques->question(this,"","Скриншот будет потерян! Вы действительно хотите закрыть редактор?");
            if (reply == QMessageBox::Yes){*/
                emit quitReader(false);
            /*}
            delete ques;
            ques = nullptr;*/
        }
        else{
           emit quitReader(false);
        }
        break;
    }
    default:
        break;
    }
    //QWidget::keyPressEvent(event);
 }
void TabGraphicsEditor::keyReleaseEvent(QKeyEvent *event){

}

TabGraphicsEditor::~TabGraphicsEditor(){
    if(m_scene)
        delete m_scene;
    if(m_graphicsWiev)
        delete m_graphicsWiev;
    if(m_panel)
        delete m_panel;
    if(m_vBoxLayout)
        delete m_vBoxLayout;
    if(m_toolTips){
    for(int i = 0; i < 11;i++){
        if(m_toolTips->data()[i]){

            delete m_toolTips->data()[i];
            m_toolTips->data()[i] = nullptr;
        }
    }
    delete m_toolTips;
    m_toolTips = nullptr;
    }

}
