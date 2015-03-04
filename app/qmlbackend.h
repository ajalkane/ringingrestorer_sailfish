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
#ifndef QMLBACKEND_H
#define QMLBACKEND_H

#include <QObject>

#include "controlclient.h"

class QmlBackend : public QObject
{
    Q_OBJECT
    ControlClient *_controlClient;

    bool _daemonActive;
    bool _daemonRunning;

    Q_PROPERTY(bool daemonActive READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool daemonRunning READ daemonRunning NOTIFY daemonRunningChanged)

    void _initDaemonState();
public:
    explicit QmlBackend(ControlClient *controlClient, QObject *parent = 0);

    bool isActive() const;
    void setActive(bool isActive);
    bool daemonRunning() const;

signals:
    void activeChanged();
    void daemonRunningChanged();

public slots:    
    void daemonActiveChanged(bool active);
    void daemonStarted();
    void daemonStopped();

    inline bool isJollaStoreCrippled() const {
#ifdef RR_JOLLA_STORE_CRIPPLED
        return true;
#else
        return false;
#endif
    }

};

#endif // QMLBACKEND_H
