#ifndef TABGRAPHICSEDITOR_H
#define TABGRAPHICSEDITOR_H

#include <QGraphicsView>
#include "inc\screenscene.h"

class TabGraphicsEditor : public QGraphicsView{
    Q_OBJECT
    ScreenScene * m_scene;
public:
    TabGraphicsEditor(bool isFullScreen,QWidget *parent = 0);
    ~TabGraphicsEditor();
signals:
    void enterSavePixmap();
public slots:
    void deleteCitrain();
};

#endif // TABGRAPHICSEDITOR_H
