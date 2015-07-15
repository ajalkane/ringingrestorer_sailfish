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
#include <QMap>
#include <QDebug>

#include "systemalignedtimer.h"

namespace {
    // Copied from nemo-keepalive/backgroundactivity
    enum Frequency
    {                                       // ORIGIN:
      Range             =            0, // Nemomobile
      ThirtySeconds     =           30, // Meego
      TwoAndHalfMinutes =  30 + 2 * 60, // Meego
      FiveMinutes       =       5 * 60, // Meego
      TenMinutes        =      10 * 60, // Meego
      FifteenMinutes    =      15 * 60, // Android
      ThirtyMinutes     =      30 * 60, // Meego & Android
      OneHour           =  1 * 60 * 60, // Meego & Android
      TwoHours          =  2 * 60 * 60, // Meego
      FourHours         =  4 * 60 * 60, // Nemomobile
      EightHours        =  8 * 60 * 60, // Nemomobile
      TenHours          = 10 * 60 * 60, // Meego
      TwelveHours       = 12 * 60 * 60, // Android
      TwentyFourHours   = 24 * 60 * 60, // Android

      MaximumFrequency  =   0x7fffffff // due to 32-bit libiphb ranges
    };

    // Map instead of hash as order of iteration is important
    QMap<quint64, uint> secsToSlotMap = QMap<quint64, uint>();
}

void _initializeSecsToSlotMap() {
    if (secsToSlotMap.isEmpty()) {
        secsToSlotMap[30] = ThirtySeconds;
        secsToSlotMap[30 + 2 * 60] = TwoAndHalfMinutes;
        secsToSlotMap[5 * 60] = FiveMinutes;
        secsToSlotMap[10 * 60] = TenMinutes;
        secsToSlotMap[30 * 60] = ThirtyMinutes;
        secsToSlotMap[1 * 60 * 60] = OneHour;
        secsToSlotMap[2 * 60 * 60] = TwoHours;
    }
}

SystemAlignedTimer::SystemAlignedTimer(QObject *parent)
    : QObject(parent)
{
    _initializeSecsToSlotMap();

    connect(&_heartbeat, &Heartbeat::timeout, this, &SystemAlignedTimer::hbTimeout);
}

void
SystemAlignedTimer::start(int secs) {
    QDateTime now = QDateTime::currentDateTime();
    _targetTime = now.addSecs(secs);

    _scheduleNextWakeup(now);
}

void
SystemAlignedTimer::_scheduleNextWakeup(const QDateTime &now) {
    qint64 secsTo = now.secsTo(_targetTime);

    int slot = _calculateNearestSlot(secsTo);

    _heartbeat.start(slot);
}

int
SystemAlignedTimer::_calculateNearestSlot(quint64 secsTo) const {
    qDebug() << Q_FUNC_INFO << "secsTo" << secsTo;

    QMap<quint64, uint>::const_iterator iter = secsToSlotMap.constBegin();
    uint lastSlot = 30; // Failsafe, the for loop should always run
    for (; iter != secsToSlotMap.constEnd(); ++iter) {
        qDebug() << Q_FUNC_INFO << "considering sec" << iter.key() << "against slot" << iter.value();
        if (secsTo <= iter.key()) {
            qDebug() << Q_FUNC_INFO  << "chose slot" << iter.value();
            return iter.value();
        }
        lastSlot = iter.value();
    }

    qDebug() << Q_FUNC_INFO  << "iterated to end, choosing last slot" << lastSlot;
    return lastSlot;
}

void
SystemAlignedTimer::stop() {
    qDebug() << Q_FUNC_INFO << "stopped timeout";
    _heartbeat.stop();
    _targetTime = QDateTime();
}

void
SystemAlignedTimer::hbTimeout() {
    if (_targetTime.isNull()) {
        qDebug() << Q_FUNC_INFO << "hbTimeout but targetTime was null, ignoring";
        return;
    }
    _heartbeat.stop();

    QDateTime now = QDateTime::currentDateTime();
    qDebug() << Q_FUNC_INFO  << "timeout reached at" << now << ", targetTime" << _targetTime;
    if (now < _targetTime) {
        _scheduleNextWakeup(now);
    } else {
        qDebug() << Q_FUNC_INFO  << "hbTimeout, emitting wakeup";
        emit timeout();
    }
}
