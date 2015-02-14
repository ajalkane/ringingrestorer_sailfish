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
#include <QtQuick>
#include <QtDebug>

#include <sailfishapp.h>

// Copied from: https://github.com/sailfishos-patches/partnerspacemanager/blob/master/README.md
// Add the following to the .pro to alllow access to private headers
// until this API makes it into a Qt release: QT += gui-private
#include <qpa/qplatformnativeinterface.h>

#include "profileclient.h"
#include "configuration.h"
#include "preferences.h"
#include "qmlbackend.h"
#include "logic/profilechangewatcher.h"
#include "interface/controlinterface.h"

int main(int argc, char *argv[])
{
    qDebug() << Q_FUNC_INFO << "Starting ringingrestorer daemon";
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    ProfileClient profileClient;
    Preferences preferences;
    Configuration::readPreferences(preferences);
    ProfileChangeWatcher profileChangeWatcher(&profileClient, &preferences);
    QmlBackend qmlBackend(&profileChangeWatcher, view.data());
    ControlInterface interface(&preferences, &profileChangeWatcher);

    if (interface.init()) {
        fprintf(stderr, "Exiting\n");
        return -1;
    }

    view->rootContext()->setContextProperty("APP_VERSION", APP_VERSION);
    view->rootContext()->setContextProperty("backend", &qmlBackend);

    view->setSource(SailfishApp::pathTo("qml/main.qml"));

    profileChangeWatcher.connect(&profileClient, SIGNAL(profileChanged(QString)), &profileChangeWatcher, SLOT(profileChanged(QString)));

    int retVal = 0;
    // Here's a loop because when the daemon window is closed, the application event loop is exited.
    // There's probably a more proper way to do this, but this works and so is sufficient for now.
    while (retVal == 0) {
        qDebug() << Q_FUNC_INFO << "Calling exec";
        retVal = app->exec();
        qDebug() << Q_FUNC_INFO << "Exec returned with value" << retVal;
    }

    qDebug() << Q_FUNC_INFO << "Exiting";
    return retVal;

}
