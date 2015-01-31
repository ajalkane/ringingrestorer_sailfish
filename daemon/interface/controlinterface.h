#ifndef CONTROLINTERFACE_H
#define CONTROLINTERFACE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>

#include "../preferences.h"
#include "../logic/profilechangewatcher.h"

class ControlInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ajalkane.ringingrestorer")
    Preferences *_preferences;
    ProfileChangeWatcher *_profileChangeWatcher;

public:
    explicit ControlInterface(Preferences *preferences, ProfileChangeWatcher *profileChangeWatcher, QObject *parent = 0);
    virtual ~ControlInterface();

    // Return 0 if success
    int init();
signals:
    void activeChanged(bool isActive);
    void started();
    void stopped();
public slots:
    // Returns true if ringing restoring is active
    bool isActive() const;
    void setActive(bool active);

private:
    bool _started;
    void _preferencesChanged();
};

#endif // CONTROLINTERFACE_H
