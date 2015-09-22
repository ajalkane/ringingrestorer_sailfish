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

import QtQuick 2.0

import QtQuick 2.0
import Sailfish.Silica 1.0


Dialog {
    id: root

    function formatMinutes(minutes) {
        if (minutes <= 60) {
            return minutes + " minutes"
        }
        else {
            var hours = Math.floor(minutes / 60)
            var remainingMins = minutes % 60
            if (remainingMins === 0) {
                return hours + " hours"
            } else {
                return hours + "h" + remainingMins + "mins"
            }
        }
    }

    function hourPartFromTotalMinutes(minutes) {
        return Math.floor(minutes / 60)
    }

    function minutePartFromTotalMinutes(minutes) {
        return minutes % 60
    }

    function restoreToMinutes() {
        return restorePicker.hour * 60 + restorePicker.minute
    }

    function restoreText() {
       var minutes = root.restoreToMinutes()
       var time = backend.timeCurrentPlusMinutes(minutes)
       return "Restore ringing in " + root.formatMinutes(minutes) + ", at " + time
    }

    onAccepted: {
        console.log("onAccepted, mins: " + root.restoreToMinutes() + ", volume: " + volumeSlider.value)
        backend.restoreRingingIn(root.restoreToMinutes(), volumeSlider.value)
    }
    onRejected: {
        console.log("onRejected")
        backend.close();
    }
    onStatusChanged: {
        console.log("onStatusChanged", status)

        if (status === PageStatus.Active) {
            console.log("Starting cancel timer")
            cancelTimer.countDown = 15
            cancelTimer.running = true
        } else {
            console.log("Cancelling cancel timer")
            cancelTimer.running = false
        }
    }

    Column {
        anchors.fill: parent

        spacing: 50

        DialogHeader {
            id: dialogHeader
            acceptText: "Accept"
            cancelText: "Cancel" + (cancelTimer.running ? " in " + cancelTimer.countDown + "s" : "");
        }

        Label {
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            text: restorePicker.label
        }

        TimePicker {
            id: restorePicker

            // Don't know why this don't work, so set x coordinate manually
            // horizontalCenter: parent.horizontalCenter
            x: parent.width / 2 - width / 2

            hour: hourPartFromTotalMinutes(backend.lastRestoreRingingInMinutes())
            minute: minutePartFromTotalMinutes(backend.lastRestoreRingingInMinutes())

            property string label: restoreText()

            onHourChanged: valueChanged();
            onMinuteChanged: valueChanged();

            function valueChanged() {
                if (cancelTimer !== null) cancelTimer.running = false
            }
        }

        Slider {
            id: volumeSlider
            label: value + "% volume"
            minimumValue: 20;
            maximumValue: 100;
            value: backend.lastRestoreRingingInVolume()
            stepSize: 20
            width: parent.width

            onValueChanged: {
                if (cancelTimer !== null) cancelTimer.running = false;
            }
        }

        Timer {
            id: cancelTimer
            interval: 1000;
            repeat: true
            property int countDown

            onTriggered: {
                console.log("Cancel timer", countDown)
                countDown--
                if (countDown <= 0) {
                    cancelTimer.running = false;
                    rejected()
                }
            }
        }
    }
}



