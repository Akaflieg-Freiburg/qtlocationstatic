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

#ifndef QDECLARATIVESEARCHSUGGESTIONMODEL_P_H
#define QDECLARATIVESEARCHSUGGESTIONMODEL_P_H

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
#include <QtLocation/private/qdeclarativesearchmodelbase_p.h>

#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE

class QDeclarativeGeoServiceProvider;
class QGeoServiceProvider;

class Q_LOCATION_PRIVATE_EXPORT QDeclarativeSearchSuggestionModel : public QDeclarativeSearchModelBase
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PlaceSearchSuggestionModel)
    QML_ADDED_IN_VERSION(5, 0)

    Q_PROPERTY(QString searchTerm READ searchTerm WRITE setSearchTerm NOTIFY searchTermChanged)
    Q_PROPERTY(QStringList suggestions READ suggestions NOTIFY suggestionsChanged)

public:
    explicit QDeclarativeSearchSuggestionModel(QObject *parent = nullptr);
    ~QDeclarativeSearchSuggestionModel();

    QString searchTerm() const;
    void setSearchTerm(const QString &searchTerm);

    QStringList suggestions() const;

    void clearData(bool suppressSignal = false) override;

    // From QAbstractListModel
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    enum Roles {
        SearchSuggestionRole = Qt::UserRole
    };

protected Q_SLOTS:
    void queryFinished() override;

Q_SIGNALS:
    void searchTermChanged();
    void suggestionsChanged();

protected:
    QPlaceReply *sendQuery(QPlaceManager *manager, const QPlaceSearchRequest &request) override;

private:
    QStringList m_suggestions;
};

QT_END_NAMESPACE

#endif
