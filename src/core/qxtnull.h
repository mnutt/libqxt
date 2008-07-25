/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/

#ifndef QXTNULL_H
#define QXTNULL_H

#include <qxtglobal.h>

/**
\class QxtNull QxtNull

\ingroup QxtCore

\brief An object representing the "null" value for QxtNullable.

\sa QxtNullable
*/

struct QXT_CORE_EXPORT QxtNull
{
    /** integer cast operator
     * In expressions, QxtNull behaves as an integer zero for compatibility with generic functions.
     */
    operator int() const
    {
        return 0;
    }
    enum { isNull = true };

    /** A predefined null object that can be assigned to any QxtNullable object.
     */
    static const QxtNull null;
};

#ifndef QXT_NO_MACROS

/*! \relates QxtNull
 * A convenience alias for QxtNull::null.
 */
#define SKIP QxtNull::null

#endif // QXT_NO_MACROS

#endif // QXTNULL_H
