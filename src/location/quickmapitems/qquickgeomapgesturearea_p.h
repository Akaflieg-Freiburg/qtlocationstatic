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

#ifndef QQUICKGEOMAPGESTUREAREA_P_H
#define QQUICKGEOMAPGESTUREAREA_P_H

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

#include <QtCore/QPointer>
#include <QtQuick/QQuickItem>
#include <QTouchEvent>
#include <QDebug>
#include <QElapsedTimer>
#include <QtPositioning/qgeocoordinate.h>
#include <QtGui/QVector2D>

QT_BEGIN_NAMESPACE

class QGraphicsSceneMouseEvent;
class QQuickGeoCoordinateAnimation;
class QDeclarativeGeoMap;
class QTouchEvent;
class QWheelEvent;
class QGeoMap;

class Q_LOCATION_PRIVATE_EXPORT QGeoMapPinchEvent : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MapPinchEvent)
    QML_UNCREATABLE("(Map)PinchEvent is not intended instantiable by developer.")
    QML_ADDED_IN_VERSION(5, 0)

    Q_PROPERTY(QPointF center READ center)
    Q_PROPERTY(qreal angle READ angle)
    Q_PROPERTY(QPointF point1 READ point1)
    Q_PROPERTY(QPointF point2 READ point2)
    Q_PROPERTY(int pointCount READ pointCount)
    Q_PROPERTY(bool accepted READ accepted WRITE setAccepted)

public:
    QGeoMapPinchEvent(const QPointF &center, qreal angle,
                      const QPointF &point1, const QPointF &point2,
                      int pointCount = 0, bool accepted = true)
        : QObject(), m_center(center), m_angle(angle),
          m_point1(point1), m_point2(point2),
          m_pointCount(pointCount), m_accepted(accepted)
    {}
    QGeoMapPinchEvent() = default;

    QPointF center() const { return m_center; }
    void setCenter(const QPointF &center) { m_center = center; }
    qreal angle() const { return m_angle; }
    void setAngle(qreal angle) { m_angle = angle; }
    QPointF point1() const { return m_point1; }
    void setPoint1(const QPointF &p) { m_point1 = p; }
    QPointF point2() const { return m_point2; }
    void setPoint2(const QPointF &p) { m_point2 = p; }
    int pointCount() const { return m_pointCount; }
    void setPointCount(int count) { m_pointCount = count; }
    bool accepted() const { return m_accepted; }
    void setAccepted(bool a) { m_accepted = a; }

private:
    QPointF m_center;
    qreal m_angle = 0.0;
    QPointF m_point1;
    QPointF m_point2;
    int m_pointCount = 0;
    bool m_accepted = true;
};

class Q_LOCATION_PRIVATE_EXPORT QQuickGeoMapGestureArea: public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MapGestureArea)
    QML_UNCREATABLE("(Map)GestureArea is not intended instantiable by developer.")
    QML_ADDED_IN_VERSION(5, 0)
    Q_ENUMS(GeoMapGesture)
    Q_FLAGS(AcceptedGestures)

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool pinchActive READ isPinchActive NOTIFY pinchActiveChanged)
    Q_PROPERTY(bool panActive READ isPanActive NOTIFY panActiveChanged)
    Q_PROPERTY(bool rotationActive READ isRotationActive NOTIFY rotationActiveChanged)
    Q_PROPERTY(bool tiltActive READ isTiltActive NOTIFY tiltActiveChanged)
    Q_PROPERTY(AcceptedGestures acceptedGestures READ acceptedGestures WRITE setAcceptedGestures NOTIFY acceptedGesturesChanged)
    Q_PROPERTY(qreal maximumZoomLevelChange READ maximumZoomLevelChange WRITE setMaximumZoomLevelChange NOTIFY maximumZoomLevelChangeChanged)
    Q_PROPERTY(qreal flickDeceleration READ flickDeceleration WRITE setFlickDeceleration NOTIFY flickDecelerationChanged)
    Q_PROPERTY(bool preventStealing READ preventStealing WRITE setPreventStealing NOTIFY preventStealingChanged REVISION(5, 1))

public:
    QQuickGeoMapGestureArea(QDeclarativeGeoMap *map);
    ~QQuickGeoMapGestureArea();

    enum GeoMapGesture {
        NoGesture = 0x0000,
        PinchGesture = 0x0001,
        PanGesture = 0x0002,
        FlickGesture = 0x0004,
        RotationGesture = 0x0008,
        TiltGesture = 0x0010,
        AllGestures = 0xffff
    };

    Q_DECLARE_FLAGS(AcceptedGestures, GeoMapGesture)

    AcceptedGestures acceptedGestures() const;
    void setAcceptedGestures(AcceptedGestures acceptedGestures);

    bool isPinchActive() const;
    bool isRotationActive() const;
    bool isTiltActive() const;
    bool isPanActive() const;
    bool isActive() const;

    bool enabled() const;
    void setEnabled(bool enabled);

    qreal maximumZoomLevelChange() const;
    void setMaximumZoomLevelChange(qreal maxChange);

    qreal flickDeceleration() const;
    void setFlickDeceleration(qreal deceleration);

    void handleTouchEvent(QPointerEvent *event);
#if QT_CONFIG(wheelevent)
    void handleWheelEvent(QWheelEvent *event);
#endif
    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseMoveEvent(QMouseEvent *event);
    void handleMouseReleaseEvent(QMouseEvent *event);
    void handleTouchUngrabEvent();

    void setMinimumZoomLevel(qreal min);
    qreal minimumZoomLevel() const;

    void setMaximumZoomLevel(qreal max);
    qreal maximumZoomLevel() const;

    void setMap(QGeoMap* map);

    bool preventStealing() const;
    void setPreventStealing(bool prevent);

Q_SIGNALS:
    void panActiveChanged();
    void pinchActiveChanged();
    void rotationActiveChanged();
    void tiltActiveChanged();
    void enabledChanged();
    void maximumZoomLevelChangeChanged();
    void acceptedGesturesChanged();
    void flickDecelerationChanged();
    void pinchStarted(QGeoMapPinchEvent *pinch);
    void pinchUpdated(QGeoMapPinchEvent *pinch);
    void pinchFinished(QGeoMapPinchEvent *pinch);
    void panStarted();
    void panFinished();
    void flickStarted();
    void flickFinished();
    void rotationStarted(QGeoMapPinchEvent *pinch);
    void rotationUpdated(QGeoMapPinchEvent *pinch);
    void rotationFinished(QGeoMapPinchEvent *pinch);
    void tiltStarted(QGeoMapPinchEvent *pinch);
    void tiltUpdated(QGeoMapPinchEvent *pinch);
    void tiltFinished(QGeoMapPinchEvent *pinch);
    void preventStealingChanged();
private:
    void update();

    // Create general data relating to the touch points
    void touchPointStateMachine();
    void startOneTouchPoint();
    void updateOneTouchPoint();
    void startTwoTouchPoints();
    void updateTwoTouchPoints();

    // All two fingers vertical parallel panning related code, which encompasses tilting
    void tiltStateMachine();
    bool canStartTilt();
    void startTilt();
    void updateTilt();
    void endTilt();

    // All two fingers rotation related code, which encompasses rotation
    void rotationStateMachine();
    bool canStartRotation();
    void startRotation();
    void updateRotation();
    void endRotation();

    // All pinch related code, which encompasses zoom
    void pinchStateMachine();
    bool canStartPinch();
    void startPinch();
    void updatePinch();
    void endPinch();

    // Pan related code (regardles of number of touch points),
    // includes the flick based panning after letting go
    void panStateMachine();
    bool canStartPan();
    void updatePan();
    bool tryStartFlick();
    void startFlick(int dx, int dy, int timeMs = 0);
    void stopFlick();

    bool pinchEnabled() const;
    void setPinchEnabled(bool enabled);
    bool rotationEnabled() const;
    void setRotationEnabled(bool enabled);
    bool tiltEnabled() const;
    void setTiltEnabled(bool enabled);
    bool panEnabled() const;
    void setPanEnabled(bool enabled);
    bool flickEnabled() const;
    void setFlickEnabled(bool enabled);

private Q_SLOTS:
    void handleFlickAnimationStopped();


private:
    void stopPan();
    void clearTouchData();
    void updateFlickParameters(const QPointF &pos);

private:
    QGeoMap* m_map = nullptr;
    QDeclarativeGeoMap *m_declarativeMap = nullptr;
    bool m_enabled = true;

    // This should be intended as a "two fingers gesture" struct
    struct Pinch
    {
        QGeoMapPinchEvent m_event;
        bool m_pinchEnabled = true;
        bool m_rotationEnabled = true;
        bool m_tiltEnabled = true;
        struct Zoom
        {
            qreal m_minimum = 0.0;
            qreal m_maximum = 30.0;
            qreal m_start = 0.0;
            qreal m_previous = 0.0;
            qreal maximumChange = 4.0;
        } m_zoom;

        struct Rotation
        {
            qreal m_startBearing = 0.0;
            qreal m_previousTouchAngle = 0.0; // needed for detecting crossing +- 180 in a safer way
            qreal m_totalAngle = 0.0;
        } m_rotation;

        struct Tilt
        {
            QPointF m_startTouchCentroid;
            qreal m_startTilt;
        } m_tilt;

        QPointF m_lastPoint1;
        QPointF m_lastPoint2;
        qreal m_startDist = 0.0;
        qreal m_lastAngle = 0.0;
     } m_pinch;

    AcceptedGestures m_acceptedGestures = AllGestures;

    struct Pan
    {
        qreal m_maxVelocity = 2500;
        qreal m_deceleration = 2500;
        QQuickGeoCoordinateAnimation *m_animation = nullptr;
        bool m_flickEnabled = true;
        bool m_panEnabled = true;
    } m_flick;


    // these are calculated regardless of gesture or number of touch points
    QVector2D m_flickVector;
    QElapsedTimer m_lastPosTime;
    QPointF m_lastPos;
    QList<QTouchEvent::TouchPoint> m_allPoints;
    QList<QTouchEvent::TouchPoint> m_touchPoints;
    QPointF m_sceneStartPoint1;

    // only set when two points in contact
    QPointF m_sceneStartPoint2;
    QGeoCoordinate m_startCoord;
    QGeoCoordinate m_touchCenterCoord;
    qreal m_twoTouchAngle;
    qreal m_twoTouchAngleStart;
    qreal m_distanceBetweenTouchPoints;
    qreal m_distanceBetweenTouchPointsStart;
    QPointF m_twoTouchPointsCentroidStart;
    QPointF m_touchPointsCentroid;
    bool m_preventStealing = false;

private:
    // prototype state machine...
    enum TouchPointState
    {
        touchPoints0,
        touchPoints1,
        touchPoints2
    } m_touchPointState;

    enum PinchState
    {
        pinchInactive,
        pinchInactiveTwoPoints,
        pinchActive
    } m_pinchState;

    enum RotationState
    {
        rotationInactive,
        rotationInactiveTwoPoints,
        rotationActive
    } m_rotationState;

    enum TiltState
    {
        tiltInactive,
        tiltInactiveTwoPoints,
        tiltActive
    } m_tiltState;

    enum FlickState
    {
        flickInactive,
        panActive,
        flickActive
    } m_flickState;

    inline void setTouchPointState(TouchPointState state);
    inline void setFlickState(FlickState state);
    inline void setTiltState(TiltState state);
    inline void setRotationState(RotationState state);
    inline void setPinchState(PinchState state);
};

QT_END_NAMESPACE
QML_DECLARE_TYPE(QQuickGeoMapGestureArea)

#endif // QQUICKGEOMAPGESTUREAREA_P_H
