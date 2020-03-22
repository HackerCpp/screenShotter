#include "inc/settings/autoplay.h"
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>
#include <QDebug>

AutoPlay::AutoPlay(){
    m_settings = new QSettings();
    QVariant autoPlay =  m_settings->value("/Settings/Base/autoPlay");
    m_isAutoPlay = autoPlay.isNull() ? false : autoPlay.toBool();
}
void autoPlayEnable(){
#ifdef Q_OS_WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    QString str = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    settings.setValue(QCoreApplication::applicationName(),str);
    settings.sync();
#endif

#ifdef Q_OS_LINUX
    QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
    QDir autorunDir(autostartPath);
    if(!autorunDir.exists()){
        qDebug() << "нет такой директории";
        autorunDir.mkpath(autostartPath);
    }
    qDebug() << autostartPath + QLatin1String("/ScreenShot.desktop");
    QFile autorunFile(autostartPath + QLatin1String("/AutorunLinux.desktop"));
    /*autorunFile.open(QFile::ReadOnly);
    qDebug() << autorunFile.readAll().size();*/
    if(!autorunFile.exists()){
        if(autorunFile.open(QFile::WriteOnly)){
            QString autorunContent("[Desktop Entry]\n"
                                       "Type=Application\n"
                                       "Exec=" +  QCoreApplication::applicationFilePath() + "\n"
                                       "Hidden=false\n"
                                       "NoDisplay=false\n"
                                       "X-GNOME-Autostart-enabled=true\n"
                                       "Name[en_GB]=ScreenShot\n"
                                       "Name=ScreenShot\n"
                                       "Comment[en_GB]=ScreenShot\n"
                                       "Comment=ScreenShot\n");
            QTextStream outStream(&autorunFile);
            outStream << autorunContent;
            autorunFile.setPermissions(QFileDevice::ExeUser|QFileDevice::ExeOwner|QFileDevice::ExeOther|QFileDevice::ExeGroup|
                                       QFileDevice::WriteUser|QFileDevice::ReadUser);
            autorunFile.close();
        }
    }

#endif
}
void AutoPlayDisable(){
#ifdef Q_OS_WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.remove(QCoreApplication::applicationName());
#endif
#ifdef Q_OS_LINUX
    QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
    QFile autorunFile(autostartPath + QLatin1String("/AutorunLinux.desktop"));
    if(autorunFile.exists()) autorunFile.remove();
#endif
}

bool AutoPlay::setAutoPlay(bool isAutoPlay){
    m_settings->setValue("/Settings/Base/autoPlay",isAutoPlay);
    QVariant autoPlay =  m_settings->value("/Settings/Base/autoPlay");
    m_isAutoPlay = autoPlay.isNull() ? false : autoPlay.toBool();
    if(m_isAutoPlay == isAutoPlay){
        m_isAutoPlay?autoPlayEnable():AutoPlayDisable();
        return true;
    }
    else
        return false;
}
bool AutoPlay::isAutoPlay(){
    return m_isAutoPlay;
}
AutoPlay::~AutoPlay(){
    if(m_settings){
        delete m_settings;
        m_settings = nullptr;
    }
}
