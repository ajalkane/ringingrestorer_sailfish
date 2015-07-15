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
    Label {
        textFormat: Text.RichText
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
        width: parent.width
        text: "RingingRestorer\n"
              + "(c) Arto Jalkanen 2015<br>"
              + "e-mail: ajalkane@gmail.com<p>"
              + "RingingRestorer icon by ssahla<p>"
              + '<a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=499LF83BBX5RY">'
              + "Please donate if you like this application</a>"
        onLinkActivated: {
            Qt.openUrlExternally(link)
        }
    }
}
