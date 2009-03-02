/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtGui module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/
#ifndef QXTSCREENUTIL_H
#define QXTSCREENUTIL_H

#include <QSize>
#include <QList>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtScreenUtilPrivate;

class QXT_GUI_EXPORT QxtScreenUtil
{
public:
    QxtScreenUtil(int screen = -1);
    ~QxtScreenUtil();

    int screen() const;
    void setScreen(int screen);

    QList<QSize> availableResolutions() const;
    QList<int> availableRefreshRates(const QSize& resolution) const;

    QSize resolution() const;
    void setResolution(const QSize& resolution);

    int refreshRate() const;
    void setRefreshRate(int rate);

    bool apply();
    bool cancel();

private:
    QXT_DECLARE_PRIVATE(QxtScreenUtil);
};

#endif // QXTSCREENUTIL_H
