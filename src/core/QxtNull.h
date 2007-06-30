/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/

#ifndef QXTNULL_DEFINED
#define QXTNULL_DEFINED
#include <QxtDefines.h>


/**
\class QxtNull QxtNull


\ingroup core 

\brief An object representing the "null" value for QxtNullable. 

seealso: QxtNullable
*/

struct QXT_CORE_EXPORT QxtNull {
/** integer cast operator
 * In expressions, QxtNull behaves as an integer zero for compatibility with generic functions.
 */
    operator int() const { return 0; }
    enum { isNull = true };
} 
/*! \relates QxtNull
 * A predefined null object that can be assigned to any QxtNullable object.
 */
qxtNull;

#ifndef QXT_NO_MACROS
/*! \relates QxtNull
 * A convenience alias for qxtNull.
 */
#define SKIP qxtNull
#endif

#endif
