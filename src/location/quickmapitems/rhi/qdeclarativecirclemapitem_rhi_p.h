/****************************************************************************
**
** Copyright (C) 2020 Paolo Angelelli <paolo.angelelli@gmail.com>
** Copyright (C) 2022 The Qt Company Ltd.
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

#ifndef QDECLARATIVECIRCLEMAPITEM_RHI_P_H
#define QDECLARATIVECIRCLEMAPITEM_RHI_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtLocation/private/qlocationglobal_p.h>
#include <QtLocation/private/qdeclarativecirclemapitem_p_p.h>
#include <QtLocation/private/qdeclarativepolygonmapitem_p_p.h>

#include "qdeclarativepolygonmapitem_rhi_p.h"

QT_BEGIN_NAMESPACE

class Q_LOCATION_PRIVATE_EXPORT QDeclarativeCircleMapItemPrivateOpenGL: public QDeclarativeCircleMapItemPrivate
{
public:
    QDeclarativeCircleMapItemPrivateOpenGL(QDeclarativeCircleMapItem &circle)
        : QDeclarativeCircleMapItemPrivate(circle)
    {
    }

    ~QDeclarativeCircleMapItemPrivateOpenGL() override;

    void onLinePropertiesChanged() override
    {
        m_circle.m_dirtyMaterial = true;
        afterViewportChanged();
    }
    void markScreenDirtyAndUpdate()
    {
        // preserveGeometry is cleared in updateMapItemPaintNode
        m_geometry.markScreenDirty();
        m_borderGeometry.markScreenDirty();
        m_circle.polishAndUpdate();
    }
    void markSourceDirtyAndUpdate() override
    {
        updateCirclePath();
        preserveGeometry();
        m_geometry.markSourceDirty();
        m_borderGeometry.markSourceDirty();
        m_circle.polishAndUpdate();
    }
    void preserveGeometry()
    {
        m_geometry.setPreserveGeometry(true, m_leftBound);
        m_borderGeometry.setPreserveGeometry(true, m_leftBound);
    }
    void onMapSet() override
    {
        markSourceDirtyAndUpdate();
    }
    void onGeoGeometryChanged() override
    {

        markSourceDirtyAndUpdate();
    }
    void onItemGeometryChanged() override
    {
        onGeoGeometryChanged();
    }
    void afterViewportChanged() override
    {
        preserveGeometry();
        markScreenDirtyAndUpdate();
    }
    void updatePolish() override;
    QSGNode * updateMapItemPaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *data) override;
    bool contains(const QPointF &point) const override;

    QGeoMapPolygonGeometryOpenGL m_geometry;
    QGeoMapPolylineGeometryOpenGL m_borderGeometry;
    QDeclarativePolygonMapItemPrivateOpenGL::RootNode *m_rootNode = nullptr;
    MapPolygonNodeGL *m_node = nullptr;
    MapPolylineNodeOpenGLExtruded *m_polylinenode = nullptr;
};

QT_END_NAMESPACE

#endif // QDECLARATIVECIRCLEMAPITEM_RHI_P_H