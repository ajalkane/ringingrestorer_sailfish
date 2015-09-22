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
#include <QTime>
#include <QDebug>

#include <sailfishapp.h>

// Copied from: https://github.com/sailfishos-patches/partnerspacemanager/blob/master/README.md
// Add the following to the .pro to alllow access to private headers
// until this API makes it into a Qt release: QT += gui-private
#include <qpa/qplatformnativeinterface.h>

#include "qmldaemonbackend.h"

QmlDaemonBackend::QmlDaemonBackend(ProfileChangeWatcher *profileChangeWatcher,
                       QQuickView *quickView,
                       QObject *parent) :
    QObject(parent),
    _profileChangeWatcher(profileChangeWatcher),
    _quickView(quickView),
    _lastRestoreRingingInMinutes(15),
    _lastRestoreRingingInVolume(40)
{
    connect(_profileChangeWatcher, SIGNAL(restoreRingingRequested()), SLOT(showTimeoutDialog()));
}

void
QmlDaemonBackend::showTimeoutDialog() {
    qDebug() << Q_FUNC_INFO;
    // Try making window get focus and appear
    //_quickView->close();
    // _quickView->create();

    _quickView->close();
    _quickView->create();
    QPlatformNativeInterface *native =
                     QGuiApplication::platformNativeInterface();
    native->setWindowProperty(_quickView->handle(),
//                                  QLatin1String("CATEGORY"), QString(QLatin1String("alarm")));
    QLatin1String("CATEGORY"), QString(QLatin1String("dialog")));


    // Copied from: https://github.com/sailfishos-patches/partnerspacemanager/blob/master/README.md
    _quickView->show();

    // End
//        qDebug() << Q_FUNC_INFO << "Calling show";
//        view->show();

    // _quickView->hide();
//    _quickView->show();
//    _quickView->raise();
//    _quickView->requestActivate();
    emit openTimeoutDialog();
}

void
QmlDaemonBackend::restoreRingingIn(int minutes, int volume) {
    qDebug() << Q_FUNC_INFO << "restoreRingingIn" << minutes << "minutes, " << "volume" << volume;
    _quickView->close();
    _profileChangeWatcher->restoreRingingIn(minutes, volume);
    _lastRestoreRingingInMinutes = minutes;
    _lastRestoreRingingInVolume = volume;
}

void
QmlDaemonBackend::close() {
    qDebug() << Q_FUNC_INFO;
    _quickView->close();
}

QString
QmlDaemonBackend::timeCurrentPlusMinutes(int minutes) {
    QTime result = QTime::currentTime();
    result = result.addSecs(minutes * 60);
    return result.toString("hh:mm");
}
