#include "profilechangewatcher.h"
#include "../configuration.h"

//#define PROFILE_RINGING "general"
//#define PROFILE_BEEP "meeting"
#define PROFILE_SILENT "silent"

ProfileChangeWatcher::ProfileChangeWatcher(ProfileClient *profileClient, Preferences *preferences, QObject *parent) :
    QObject(parent), _profileClient(profileClient), _restoreVolume(40), _preferences(preferences)
{
    _currentProfile = _profileClient->getProfile();
    _timer.setSingleShot(true);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(_restoreRinging()));
}

void
ProfileChangeWatcher::profileChanged(const QString &profile) {
    _restoreProfile = _currentProfile;
    _currentProfile = profile;

    qDebug("ProfileChangeWatcher::profileChanged '%s'' -> '%s'", qPrintable(_restoreProfile), qPrintable(profile));
    if (!_preferences->isActive) {
        qDebug("ProfileChangeWatcher::profileChanged not active, doing nothing");
        return;
    }
    const QString profileLower = profile.toLower();
    if (_restoreProfile.toLower() != PROFILE_SILENT && _restoreProfile != profile
            && (profileLower == PROFILE_SILENT)) {
        qDebug("ProfileChangeWatcher::profileChanged stopping and starting timer");
        emit restoreRingingRequested();
    }

    // ORIGINAL harmattan version
//    if (previousProfile.toLower() == PROFILE_RINGING && previousProfile != profile
//            && (profileLower == PROFILE_SILENT || profileLower == PROFILE_BEEP)) {
//        qDebug("ProfileChangeWatcher::profileChanged stopping and starting timer");
//        emit restoreRingingRequested();
//    }

}

void
ProfileChangeWatcher::_restoreRinging() {
    if (!_preferences->isActive) {
        qDebug("ProfileChangeWatcher::_restoreRinging not active, doing nothing");
        return;
    }

    qDebug("ProfileChangeWatcher::_restoreRinging, currentProfile '%s'", qPrintable(_currentProfile));
    if (_currentProfile.toLower() == PROFILE_SILENT) {
        qDebug("ProfileChangeWatcher::_restoreRinging, currentProfile '%s'", qPrintable(_currentProfile));
        _profileClient->setProfile(_restoreProfile);
        if (_restoreVolume > -1) {
            _profileClient->setProfileVolume(_restoreProfile, _restoreVolume);
        }

        // TODO: notification
//        MNotification notification(MNotification::DeviceEvent, "Ringing restored", "Ringing profile restored");
//        notification.setImage("icon-m-common-done");
//        notification.publish();
    }
}

void
ProfileChangeWatcher::restoreRingingIn(int minutes, int volume) {
    qDebug("ProfileChangeWatcher::restoreRingingIn %d, volume %d, currentProfile '%s'", minutes, volume, qPrintable(_currentProfile));
    _timer.stop();
#ifdef RR_TESTING
    qDebug("ProfileChangeWatcher::restoreRingingIn::RR_TESTING, using minutes as seconds");
    _timer.start(minutes * 1000);
#else
    _timer.start(minutes * 60 * 1000);
#endif
    _restoreVolume = volume;
}

void
ProfileChangeWatcher::stopRestore() {
    qDebug("ProfileChangeWatcher::stopRestore");
    _timer.stop();
}
