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

CoverBackground {
    Label {
        id: label
        horizontalAlignment: Text.AlignHCenter
        width: parent.width
        // anchors.centerIn: parent
        wrapMode: Text.WordWrap
        text: backend.daemonActive ? "RingingRestorer active"
                                   : "RingingRestorer disabled"
    }

    CoverActionList {
        id: coverAction

        CoverAction {
            iconSource: backend.daemonActive ? "image://theme/icon-cover-pause"
                                             : "image://theme/icon-cover-play"
            onTriggered: {
                console.log("CoverAction triggered")
                backend.daemonActive = !backend.daemonActive
            }
        }
    }
}


