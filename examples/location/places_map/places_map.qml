/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [Imports]
import QtQuick
import QtPositioning
import QtLocation
//! [Imports]

Rectangle {
    anchors.fill: parent

    //! [Initialize Plugin]
    Plugin {
        id: myPlugin
        name: "osm" // "maplibregl", "esri", ...
        //specify plugin parameters if necessary
        //PluginParameter {...}
        //PluginParameter {...}
        //...
    }
    //! [Initialize Plugin]

    //! [Current Location]
    PositionSource {
        id: positionSource
        property variant lastSearchPosition: locationOslo
        active: true
        updateInterval: 120000 // 2 mins
        onPositionChanged:  {
            var currentPosition = positionSource.position.coordinate
            map.center = currentPosition
            var distance = currentPosition.distanceTo(lastSearchPosition)
            if (distance > 500) {
                // 500m from last performed pizza search
                lastSearchPosition = currentPosition
                searchModel.searchArea = QtPositioning.circle(currentPosition)
                searchModel.update()
            }
        }
    }
    //! [Current Location]

    //! [PlaceSearchModel]
    property variant locationOslo: QtPositioning.coordinate( 59.93, 10.76)

    PlaceSearchModel {
        id: searchModel

        plugin: myPlugin

        searchTerm: "Pizza"
        searchArea: QtPositioning.circle(locationOslo, 500000 /* 5 km radius */)

        Component.onCompleted: update()
    }
    //! [PlaceSearchModel]

    //! [Places MapItemView]
    Map {
        id: map
        anchors.fill: parent
        plugin: myPlugin;
        center: locationOslo
        zoomLevel: 5

        MapItemView {
            model: searchModel
            delegate: MapQuickItem {
                coordinate: place.location.coordinate

                anchorPoint.x: image.width * 0.5
                anchorPoint.y: image.height

                sourceItem: Column {
                    Image { id: image; source: "marker.png" }
                    Text { text: title; font.bold: true }
                }
            }
        }
    }
    //! [Places MapItemView]

    Connections {
        target: searchModel
        function onStatusChanged() {
            if (searchModel.status == PlaceSearchModel.Error)
                console.log(searchModel.errorString());
        }
    }
}
