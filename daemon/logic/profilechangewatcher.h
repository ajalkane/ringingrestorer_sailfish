#ifndef PROFILECHANGEWATCHER_H
#define PROFILECHANGEWATCHER_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "../profileclient.h"
#include "../preferences.h"

class ProfileChangeWatcher : public QObject
{
    Q_OBJECT

    ProfileClient *_profileClient;
    QString _currentProfile;
    QString _restoreProfile;
    QTimer _timer;
    int _restoreVolume;
    Preferences *_preferences;

public:
    ProfileChangeWatcher(ProfileClient *profileClient, Preferences *preferences, QObject *parent = 0);

    void restoreRingingIn(int minutes, int volume);
    void stopRestore();
signals:
    void restoreRingingRequested();
public slots:
    void profileChanged(const QString &profile);
    // void restoreRinging(int inSeconds);
private slots:
    void _restoreRinging();
};

#endif // PROFILECHANGEWATCHER_H
