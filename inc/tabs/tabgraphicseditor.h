#ifndef TABGRAPHICSEDITOR_H
#define TABGRAPHICSEDITOR_H

#include <QGraphicsView>
#include "inc/screenscene.h"
#include "inc/panel.h"
#include "inc/panel/btntooltip.h"
#include <QSettings>

class TabGraphicsEditor : public QWidget{
    Q_OBJECT
    QSettings *m_settings;
    bool m_isMessag;
    QGraphicsView *m_graphicsWiev;
    ScreenScene * m_scene;
    Panel *m_panel;
    QVBoxLayout *m_vBoxLayout;
    QVector<ToolTip*> *m_toolTips;
    ToolTip *m_curentToolTip;
public:
    TabGraphicsEditor(bool isFullScreen,QWidget *parent = nullptr);
    virtual ~TabGraphicsEditor();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:
    void enterSavePixmap(bool isScreen = true);
    void quitReader(bool isScreen = false);
public slots:
    void savePicture(QPixmap *pict);
    void showToolTip(QPoint point,int index);
    void hideToolTip();
};

#endif // TABGRAPHICSEDITOR_H
