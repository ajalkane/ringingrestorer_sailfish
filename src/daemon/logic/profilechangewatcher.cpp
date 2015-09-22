/**********************************************************************
 * Copyright 2015 Arto Jalkanen
 *
 * This file is part of RingingRestorer.
 *
 * RingingRestorer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RingingRestorer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RingingRestorer.  If not, see <http://www.gnu.org/licenses/>
**/
#include <QDebug>

#include "profilechangewatcher.h"
#include "../configuration.h"

#define PROFILE_GENERAL "general"
//#define PROFILE_RINGING "general"
//#define PROFILE_BEEP "meeting"
#define PROFILE_SILENT "silent"

namespace {
    QStringList watchedProfiles;
}

ProfileChangeWatcher::ProfileChangeWatcher(ProfileClient *profileClient, Preferences *preferences, QObject *parent) :
    QObject(parent), _profileClient(profileClient), _restoreVolume(40), _preferences(preferences)
{
    _currentProfile = _profileClient->getProfile();
    _restoreProfile = PROFILE_GENERAL;

    connect(&_timer, SIGNAL(timeout()), this, SLOT(_restoreRinging()));
}

void
ProfileChangeWatcher::profileChanged(const QString &profile) {
    if (watchedProfiles.isEmpty()) {
        watchedProfiles << PROFILE_GENERAL << PROFILE_SILENT;
    }

    const QString profileLower = profile.toLower();

    if (!watchedProfiles.contains(profileLower)) {
        qDebug() << Q_FUNC_INFO << "profile " << profile << "is not in" << watchedProfiles<< ", ignoring for restore profile";
        return;
    }

    if (_currentProfile != profile && profileLower == PROFILE_SILENT) {
        qDebug() << Q_FUNC_INFO << "stopping and starting timer";
        emit restoreRingingRequested();
    } else {
        qDebug() << Q_FUNC_INFO << "Changed to " << profile
                 << "which is either different than currentProfile" << _currentProfile
                 << "or is not silent profile" << PROFILE_SILENT;
    }

    _currentProfile = profile;

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
        // TODO
        _profileClient->setProfileVolume(_restoreProfile, 40);
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
    _timer.start(minutes);
#else
    _timer.start(minutes * 60);
#endif
    _restoreVolume = volume;
}

void
ProfileChangeWatcher::stopRestore() {
    qDebug("ProfileChangeWatcher::stopRestore");
    _timer.stop();
}
