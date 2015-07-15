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
#ifndef QMLDAEMONBACKEND_H
#define QMLDAEMONBACKEND_H

#include <QObject>
#include <QtQuick>

#include "logic/profilechangewatcher.h"

class QmlDaemonBackend : public QObject
{
    Q_OBJECT

    ProfileChangeWatcher *_profileChangeWatcher;
    QQuickView *_quickView;

public:
    explicit QmlDaemonBackend(ProfileChangeWatcher *profileChangeWatcher,
                        QQuickView *quickView,
                        QObject *parent = 0);

signals:
    void openTimeoutDialog();
public slots:
    void showTimeoutDialog();
    void restoreRingingIn(int minutes, int volume);
    void close();
    QString timeCurrentPlusMinutes(int minutes);
};

#endif // QMLDAEMONBACKEND_H
