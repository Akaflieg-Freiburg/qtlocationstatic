/****************************************************************************
**
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

#ifndef QDECLARATIVESEARCHMODELBASE_H
#define QDECLARATIVESEARCHMODELBASE_H

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
#include <QtLocation/private/qdeclarativegeoserviceprovider_p.h>
#include <QtCore/QAbstractListModel>
#include <QtQml/QQmlParserStatus>
#include <QtLocation/QPlaceSearchRequest>
#include <QtLocation/QPlaceSearchResult>
#include <QtLocation/QPlaceReply>

QT_BEGIN_NAMESPACE

class QPlaceManager;
class QPlaceSearchRequest;
class QPlaceSearchReply;
class QDeclarativePlace;

class Q_LOCATION_PRIVATE_EXPORT QDeclarativeSearchModelBase : public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeGeoServiceProvider *plugin READ plugin WRITE setPlugin NOTIFY pluginChanged)
    Q_PROPERTY(QVariant searchArea READ searchArea WRITE setSearchArea NOTIFY searchAreaChanged)
    Q_PROPERTY(int limit READ limit WRITE setLimit NOTIFY limitChanged)
    Q_PROPERTY(bool previousPagesAvailable READ previousPagesAvailable NOTIFY previousPagesAvailableChanged)
    Q_PROPERTY(bool nextPagesAvailable READ nextPagesAvailable NOTIFY nextPagesAvailableChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)

    Q_ENUMS(Status)

    Q_INTERFACES(QQmlParserStatus)

public:
    enum Status {
        Null,
        Ready,
        Loading,
        Error
    };

    explicit QDeclarativeSearchModelBase(QObject *parent = nullptr);
    ~QDeclarativeSearchModelBase();

    QDeclarativeGeoServiceProvider *plugin() const;
    void setPlugin(QDeclarativeGeoServiceProvider *plugin);

    QVariant searchArea() const;
    void setSearchArea(const QVariant &searchArea);

    int limit() const;
    void setLimit(int limit);

    bool previousPagesAvailable() const;
    bool nextPagesAvailable() const;

    Status status() const;
    void setStatus(Status status, const QString &errorString = QString());

    Q_INVOKABLE void update();

    Q_INVOKABLE void cancel();
    Q_INVOKABLE void reset();

    Q_INVOKABLE QString errorString() const;

    Q_INVOKABLE void previousPage();
    Q_INVOKABLE void nextPage();

    virtual void clearData(bool suppressSignal = false);

    // From QQmlParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void pluginChanged();
    void searchAreaChanged();
    void limitChanged();
    void previousPagesAvailableChanged();
    void nextPagesAvailableChanged();
    void statusChanged();

protected:
    virtual void initializePlugin(QDeclarativeGeoServiceProvider *plugin);

protected Q_SLOTS:
    virtual void queryFinished() = 0;
    virtual void onContentUpdated();

private Q_SLOTS:
    void pluginNameChanged();

protected:
    virtual QPlaceReply *sendQuery(QPlaceManager *manager, const QPlaceSearchRequest &request) = 0;
    void setPreviousPageRequest(const QPlaceSearchRequest &previous);
    void setNextPageRequest(const QPlaceSearchRequest &next);

    QPlaceSearchRequest m_request;
    QDeclarativeGeoServiceProvider *m_plugin = nullptr;
    QPlaceReply *m_reply = nullptr;

private:
    bool m_complete = false;
    Status m_status = Null;
    QString m_errorString;
    QPlaceSearchRequest m_previousPageRequest;
    QPlaceSearchRequest m_nextPageRequest;
};

QT_END_NAMESPACE

#endif // QDECLARATIVESEARCHMODELBASE_H
