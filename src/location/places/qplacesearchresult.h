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

#ifndef QPLACESEARCHRESULT_H
#define QPLACESEARCHRESULT_H

#include <QtCore/QSharedDataPointer>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtLocation/qlocationglobal.h>

QT_BEGIN_NAMESPACE

#define Q_DECLARE_SEARCHRESULT_D_FUNC(Class) \
    inline Class##Private *d_func(); \
    inline const Class##Private *d_func() const;\
    friend class Class##Private;

#define Q_DECLARE_SEARCHRESULT_COPY_CTOR(Class) \
    Class(const QPlaceSearchResult &other);

class QPlaceSearchRequest;
class QPlaceSearchResultPrivate;
class QPlaceIcon;

class Q_LOCATION_EXPORT QPlaceSearchResult
{
public:
    QPlaceSearchResult();
    QPlaceSearchResult(const QPlaceSearchResult &other);

    virtual ~QPlaceSearchResult();

    QPlaceSearchResult &operator=(const QPlaceSearchResult &other);

    bool operator==(const QPlaceSearchResult &other) const;
    bool operator!=(const QPlaceSearchResult &other) const {
        return !(other == *this);
    }

    enum SearchResultType {
        UnknownSearchResult = 0,
        PlaceResult,
        ProposedSearchResult
    };

    SearchResultType type() const;

    QString title() const;
    void setTitle(const QString &title);

    QPlaceIcon icon() const;
    void setIcon(const QPlaceIcon &icon);

protected:
    explicit QPlaceSearchResult(QPlaceSearchResultPrivate *d);
    QSharedDataPointer<QPlaceSearchResultPrivate> d_ptr;

private:
    inline QPlaceSearchResultPrivate *d_func();
    inline const QPlaceSearchResultPrivate *d_func() const;

    friend class QPlaceSearchResultPrivate;
};

Q_DECLARE_TYPEINFO(QPlaceSearchResult, Q_RELOCATABLE_TYPE);

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QPlaceSearchResult)
Q_DECLARE_METATYPE(QPlaceSearchResult::SearchResultType)

#endif // QPLACESEARCHRESULT_H
