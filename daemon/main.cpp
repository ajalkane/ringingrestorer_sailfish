/*
#include <QtGui/QApplication>
#include <QtDeclarative>

#include <QtCore/QStringList>
#include <QtCore/QFileInfo>

#include <QObject>
#include <QList>

#include <MComponentData>

#include "profileclient.h"
#include "configuration.h"
#include "preferences.h"
#include "qmlbackend.h"
#include "logic/profilechangewatcher.h"
#include "interface/controlinterface.h"

#include "qmlapplicationviewer.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());
    MComponentData::createInstance(argc, argv);

    ProfileClient profileClient;
    Preferences preferences;
    Configuration::readPreferences(preferences);
    ProfileChangeWatcher profileChangeWatcher(&profileClient, &preferences);
    QmlBackend qmlBackend(&profileChangeWatcher, &(*viewer));
    ControlInterface interface(&preferences, &profileChangeWatcher);

    if (interface.init()) {
        fprintf(stderr, "Exiting\n");
        return -1;
    }

    profileChangeWatcher.connect(&profileClient, SIGNAL(profileChanged(QString)), &profileChangeWatcher, SLOT(profileChanged(QString)));
    QDeclarativeContext *ctxt = viewer->rootContext();

    ctxt->setContextProperty("backend", &qmlBackend);
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/mainDaemon.qml"));

    int retVal = 0;
    // Here's a loop because when the daemon window is closed, the application event loop is exited.
    // There's probably a more proper way to do this, but this works and so is sufficient for now.
    while (retVal == 0) {
        retVal = app->exec();
    }

    return retVal;
}
*/

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
