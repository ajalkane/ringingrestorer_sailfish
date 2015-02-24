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
import Sailfish.Silica 1.0


Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: "About"
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        Button {
            id: controlButton
            anchors.centerIn: parent;
            height: 80;
            text: !backend.daemonActive ? "Start RingingRestorer" : "Stop RingingRestorer"
            visible: backend.daemonRunning
            onClicked: {
                backend.daemonActive = !backend.daemonActive
            }
        }

        Label {
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: controlButton.bottom
                topMargin: controlButton.height / 2
            }
            text: "RingingRestorer backend is not running. If you have just started your phone, close this application, wait a couple of minutes, and then try starting the application again."
            visible: !backend.daemonRunning
        }

        Label {
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: controlButton.bottom
                topMargin: controlButton.height / 2
            }
            text: backend.daemonActive ? "RingingRestorer is active. When profile changed from ringing to silent, will ask how long until ringing resumed."
                                       : "RingingRestorer is not active"
            visible: backend.daemonRunning
        }
    }
}


