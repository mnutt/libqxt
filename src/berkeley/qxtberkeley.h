/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtBerkeley module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtbdb.h"
#include "qxtbdbhash.h"

/** \defgroup QxtBerkeley  QxtBerkeley
    \brief    A Qt Interface to the Berkeley DB

berkeley db is in wide use where relational databases, especially SQL, are not desired due to heavy overhead or its programming complexity. QxtBerkeley provides you an extremly easy to use interface to the fast and stable file based berkeley database. The API is designed after Qts tulip container classes. 


<h2>Platform specific notes</h2>
<h3>Windows</h3>
On Windows the buildsystem is unfortunatly unable to detect the berkeley db library on your system automaticly, becouse of the wide differences in naming scheme.
<br>
You will have to add the library yourself:
<br>
MSVC:
\code
configure.bat -I C:\BDB-MSVC\include -L C:\BDB-MSVC\lib -l libdb46 (or libdb45)
\endcode

MinGW (http://mathieu.carbou.free.fr/wiki/index.php?title=Berkeley_DB_for_MinGW)
\code
configure.bat -I C:\BDB-MINGW\include -L C:\BDB-MINGW\lib -l db
\endcode
<h3>Linux</h3>
If you have issues compiling QxtBerkeley with your distributions bdb package, it is suggested that you try the upstream version from http://www.oracle.com/technology/software/products/berkeley-db/index.html
*/
