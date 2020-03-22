#include "inc/settings/activewindow.h"
#ifdef Q_OS_WIN32 || Q_OS_WIN
#include <windows.h>
#else
#endif
ActiveWindow::ActiveWindow(){

}

QString ActiveWindow::getActiveWndTitle(){
#ifdef Q_OS_WIN32 || Q_OS_WIN
    char buff[256];
    HWND hwnd = GetForegroundWindow();
    GetWindowText(hwnd, (LPWSTR) buff, 254);
    QString title = QString::fromWCharArray((const wchar_t *)buff);
    return title;
#else
    return QString::number(rand()%1999);
#endif
}
