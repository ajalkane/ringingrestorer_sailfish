#ifndef QMLBACKEND_H
#define QMLBACKEND_H

#include <QObject>
#include <QtQuick>

#include "logic/profilechangewatcher.h"

class QmlBackend : public QObject
{
    Q_OBJECT

    ProfileChangeWatcher *_profileChangeWatcher;
    QQuickView *_quickView;

public:
    explicit QmlBackend(ProfileChangeWatcher *profileChangeWatcher,
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

#endif // QMLBACKEND_H
