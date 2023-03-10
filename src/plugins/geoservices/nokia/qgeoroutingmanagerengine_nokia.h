/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGEOROUTINGMANAGER_NOKIA_H
#define QGEOROUTINGMANAGER_NOKIA_H

#include "qgeoserviceproviderplugin_nokia.h"

#include <qgeoserviceprovider.h>
#include <qgeoroutingmanagerengine.h>

QT_BEGIN_NAMESPACE

class QGeoNetworkAccessManager;
class QGeoUriProvider;

class QGeoRoutingManagerEngineNokia : public QGeoRoutingManagerEngine
{
    Q_OBJECT
public:
    QGeoRoutingManagerEngineNokia(QGeoNetworkAccessManager *networkInterface,
                                  const QVariantMap &parameters,
                                  QGeoServiceProvider::Error *error,
                                  QString *errorString);
    ~QGeoRoutingManagerEngineNokia();

    QGeoRouteReply *calculateRoute(const QGeoRouteRequest &request) override;
    QGeoRouteReply *updateRoute(const QGeoRoute &route, const QGeoCoordinate &position) override;

private Q_SLOTS:
    void routeFinished();
    void routeError(QGeoRouteReply::Error error, const QString &errorString);

private:
    QStringList calculateRouteRequestString(const QGeoRouteRequest &request) const;
    QStringList updateRouteRequestString(const QGeoRoute &route, const QGeoCoordinate &position);
    QString routeRequestString(const QGeoRouteRequest &request) const;
    bool checkEngineSupport(const QGeoRouteRequest &request,
                            QGeoRouteRequest::TravelModes travelModes) const;
    QString modesRequestString(const QGeoRouteRequest &request,
                               QGeoRouteRequest::TravelModes travelModes,
                               const QString &optimization) const;
    static QString trimDouble(double degree, int decimalDigits = 10);

    QGeoNetworkAccessManager *m_networkManager;
    QGeoUriProvider *m_uriProvider;
    QString m_appId;
    QString m_token;
};

QT_END_NAMESPACE

#endif
