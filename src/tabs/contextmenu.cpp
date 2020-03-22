#include "inc/tabs/contextmenu.h"
#include <QApplication>
#include <QScreen>


ContextMenu::ContextMenu(QWidget* pwgt): QMenu(pwgt){
    m_size = QApplication::screens().at(0)->geometry();
    installEventFilter(this);
    addAction(("Опубликовать"),this,SIGNAL(global()),Qt::CTRL + Qt::Key_Return);
    addSeparator();
    addAction("&Сохранить",this,SIGNAL(save()),Qt::CTRL+Qt::Key_S);
    addSeparator();
    addAction("&Копировать",this,SIGNAL(copy()),Qt::CTRL+Qt::Key_C);
    addSeparator();

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setStyleSheet("QMenu{background-color: rgba(0, 0, 0, 0.8);color:#ffffff;}\
QMenu::Separator{height:1px;background:#5a5a5a;}");
}
bool ContextMenu::eventFilter(QObject * obj, QEvent *event){
if (event->type() == QEvent::Show){
    if(this->pos().y() < height()*2)
        return false;
    QPoint pos = this->pos() - QPoint(width() - 15,height()*2);
    move(pos);
    return true;
}
return false;
}
/*void ContextMenu::paintEvent(QPaintEvent *event){
    QPainter *painter = new QPainter(this);
    QPen pen(QColor(90,90,90));
    painter->setPen(pen);
    painter->drawRect(this->rect());
    delete painter;
 }*/
