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
        contentHeight: content.height

        PullDownMenu {
            MenuItem {
                text: "About"
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        Column {
            id: content
            width: parent.width
            spacing: 50

            Item {
              height: Theme.paddingLarge
              width: 1 // must be non zero
            }

            Button {
                id: controlButton
                anchors.horizontalCenter: parent.horizontalCenter

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
                text: !backend.isJollaStoreCrippled()
                      ? "RingingRestorer backend is not running. If you have just started your phone, close this application, wait a couple of minutes, and then try starting the application again."
                      : "RingingRestorer backend is not running. Try quitting application and starting again."
                visible: !backend.daemonRunning
            }

            Label {
                id: ringingRestoreActiveStatus
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
                text: backend.daemonActive ? "RingingRestorer is active. When profile changed from ringing to silent, will ask how long until ringing resumed."
                                           : "RingingRestorer is not active"
                visible: backend.daemonRunning
            }

            Label {
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
                text: "RingingRestorer is running. You can close this application and RingingRestorer stays active in background. "
                    + "If you reboot your phone, you will have to start the application again once for RingingRestorer to become active."
                visible: backend.daemonRunning && backend.daemonActive && backend.isJollaStoreCrippled()
            }
        } // Row
    }
}


