#ifndef CONTROLCLIENT_H
#define CONTROLCLIENT_H

#include <QObject>
#include <QList>
#include <QtDBus/QtDBus>

class ControlClient : public QObject
{
    Q_OBJECT

    QDBusInterface *dbus_iface;
public:
    explicit ControlClient(QObject *parent = 0);
    ~ControlClient();

    bool isActive() const;
    void setActive(bool isActive);

    // Returns QDBusError::ErrorType of last call. 0 is no error.
    int lastError() const;
signals:
    void activeChanged(bool);
    void started();
    void stopped();
public slots:
};

#endif // CONTROLCLIENT_H
