#ifndef AUTOPLAY_H
#define AUTOPLAY_H
#include <QSettings>

class AutoPlay{
    QSettings *m_settings;
    bool m_isAutoPlay;
public:
    AutoPlay();
    bool setAutoPlay(bool isAutoPlay);
    bool isAutoPlay();
    ~AutoPlay();
};

#endif // AUTOPLAY_H
