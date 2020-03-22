#ifndef TRAY_H
#define TRAY_H
#include <QSystemTrayIcon>
#include <QAction>


class Tray : public QSystemTrayIcon{
    Q_OBJECT
    void mousePressEvent(QMouseEvent *event);
public:
    Tray(QIcon icon);
    bool event(QEvent *event);
public slots:
    void mouseclick(QSystemTrayIcon::ActivationReason reas);
    void messageClick();
    void addMenu();
signals:
    void leftMouseClick();
    void rightMouseClick();
};

#endif // TRAY_H
