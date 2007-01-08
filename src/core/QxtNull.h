/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Adam Higerd and Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTNULL_DEFINED
#define QXTNULL_DEFINED
#include <QxtDefines.h>


/**
\class QxtNull QxtNull


\ingroup core 

\brief An object representing the "null" value for QxtNullable. 

seealso: QxtNullable
*/

struct QXT_DLLEXPORT QxtNull {
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
