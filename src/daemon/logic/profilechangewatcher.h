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
#ifndef PROFILECHANGEWATCHER_H
#define PROFILECHANGEWATCHER_H

#include <QObject>
#include <QString>

#include "../profileclient.h"
#include "../preferences.h"
#include "../systemalignedtimer.h"

class ProfileChangeWatcher : public QObject
{
    Q_OBJECT

    ProfileClient *_profileClient;
    QString _currentProfile;
    QString _restoreProfile;
    SystemAlignedTimer _timer;
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
