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
#ifndef SYSTEMALIGNEDTIMER_H
#define SYSTEMALIGNEDTIMER_H

#include <QObject>
#include <QDateTime>
#include "nemo-keepalive/heartbeat.h"

/**
 * @brief System aligned timeouts.
 *
 * Ensures timeouts happen as soon as possible in the specified time. Ensures timeouts do not happen before
 * before the specified timeout.
 *
 * When exactly the timeout is invoked depends on underlying system's timeout resolution. On sailfish it is 30 seconds,
 * so the timeout can be as much as 30 seconds after the specified target time.
 */
class SystemAlignedTimer : public QObject
{
    Q_OBJECT

    QDateTime _targetTime;
    Heartbeat _heartbeat;

    void _scheduleNextWakeup(const QDateTime &now);
    int _calculateNearestSlot(quint64 secsTo) const ;
public:
    SystemAlignedTimer(QObject *parent = 0);

    void start(int secs);
    void stop();
signals:
    void timeout();

private slots:
    void hbTimeout();
};

#endif // SYSTEMALIGNEDTIMER_H
