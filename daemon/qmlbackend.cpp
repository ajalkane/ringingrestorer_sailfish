#include <QTime>
#include <QDebug>

#include <sailfishapp.h>

// Copied from: https://github.com/sailfishos-patches/partnerspacemanager/blob/master/README.md
// Add the following to the .pro to alllow access to private headers
// until this API makes it into a Qt release: QT += gui-private
#include <qpa/qplatformnativeinterface.h>

#include "qmlbackend.h"

QmlBackend::QmlBackend(ProfileChangeWatcher *profileChangeWatcher,
                       QQuickView *quickView,
                       QObject *parent) :
    QObject(parent),
    _profileChangeWatcher(profileChangeWatcher),
    _quickView(quickView)
{
    connect(_profileChangeWatcher, SIGNAL(restoreRingingRequested()), SLOT(showTimeoutDialog()));
}

void
QmlBackend::showTimeoutDialog() {
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
QmlBackend::restoreRingingIn(int minutes, int volume) {
    qDebug() << Q_FUNC_INFO << "restoreRingingIn" << minutes << "minutes, " << "volume" << volume;
    _quickView->close();
    _profileChangeWatcher->restoreRingingIn(minutes, volume);
}

void
QmlBackend::close() {
    qDebug() << Q_FUNC_INFO;
    _quickView->close();
}

QString
QmlBackend::timeCurrentPlusMinutes(int minutes) {
    QTime result = QTime::currentTime();
    result = result.addSecs(minutes * 60);
    return result.toString("hh:mm");
}
