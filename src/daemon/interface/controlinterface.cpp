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
#include <QtDBus/QtDBus>

#include <stdio.h>

#include "controlinterface.h"

#include "../configuration.h"

#define PM_OBJECT_NAME "/org/ajalkane/ringingrestorer"
#define PM_SERVICE_NAME "org.ajalkane.ringingrestorer"

ControlInterface::ControlInterface(Preferences *preferences, ProfileChangeWatcher *profileChangeWatcher, QObject *parent) :
    QObject(parent), _preferences(preferences), _profileChangeWatcher(profileChangeWatcher)
{
}

int
ControlInterface::init() {
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerObject(PM_OBJECT_NAME, this, QDBusConnection::ExportAllSlots|QDBusConnection::ExportAllSignals)) {
        fprintf(stderr, "Could not register D-Bus object at %s. Daemon already running?\n", PM_OBJECT_NAME);
        return -1;
    }

    if (!bus.registerService(PM_SERVICE_NAME)) {
        fprintf(stderr, "Could not register D-Bus service at %s. Daemon already running?\n", PM_SERVICE_NAME);
        return -1;
    }

    emit started();
    _started = true;
    return 0;
}

ControlInterface::~ControlInterface() {
    if (_started) {
        emit stopped();
    }
    QDBusConnection bus = QDBusConnection::sessionBus();
    bus.unregisterService(PM_SERVICE_NAME);
    bus.unregisterObject(PM_OBJECT_NAME);
}

bool
ControlInterface::isActive() const {
    return _preferences->isActive;
}

void
ControlInterface::setActive(bool isActive) {
    qDebug("Set active called with %d", isActive);
    if (isActive != _preferences->isActive) {
        qDebug("Active changed to %d", isActive);
        if (isActive == false) {
            _profileChangeWatcher->stopRestore();
        }
        _preferences->isActive = isActive;

        emit activeChanged(isActive);
        _preferencesChanged();
    }
}

void
ControlInterface::_preferencesChanged() {
    Configuration::writePreferences(*_preferences);
}
