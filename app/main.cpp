#include <QtGui/QApplication>
#include <QtDeclarative>

#include "qmlapplicationviewer.h"

#include "controlclient.h"
#include "qmlbackend.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    ControlClient controlClient;
    QmlBackend qmlBackend(&controlClient);

    QDeclarativeContext *ctxt = viewer->rootContext();

    ctxt->setContextProperty("backend", &qmlBackend);

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/main.qml"));
    viewer->showExpanded();

    return app->exec();
}
