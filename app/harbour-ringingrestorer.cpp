/*/**********************************************************************
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
#include <sailfishapp.h>

#include "controlclient.h"
#include "qmlbackend.h"

int main(int argc, char *argv[])
{
    qDebug() << Q_FUNC_INFO << "Starting ringingrestorer app";
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    ControlClient controlClient;
    QmlBackend qmlBackend(&controlClient);

    view->rootContext()->setContextProperty("backend", &qmlBackend);
    view->setSource(SailfishApp::pathTo("qml/harbour-ringingrestorer.qml"));
    view->show();
    return app->exec();
}

