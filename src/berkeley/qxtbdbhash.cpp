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
#include "qxtbdbhash.h"



/*!
    \class QxtBdbHash QxtBdbHash
    \ingroup QxtBerkeley
    \brief template class that provides key/value access to a berkeley db file

    both value and key must be registered with the qt meta system.\n
    YOu may not touch the file while a QxtBdbHash instance is running on it.

    examples usage:
    \code
    QxtBdbHash<qreal,QStringList> db("test.db");
    db.insert(344.4,QStringList<<"HI"<<":)");
    qDebug()<<db[344.4];
    \endcode

    \doqsy {implicitshared}
*/

/*!
    \fn void QxtBdbHash::QxtBdbHash()

    Constructs an invalid QxtBdbHash
*/

/*!
    \fn void QxtBdbHash::QxtBdbHash(QString file)

    Constructs a QxtBdbHash, and opens the file specified as its database.
*/


/*!
    \fn bool QxtBdbHash::open(QString file)

    opens the specified file. returns true on success and false on failure. \n Note that a sanity check is performed before opening the file.
*/

/*!
    \fn void QxtBdbHash::clear

    Erase all records. This does not delete the unerlieing file.
*/


/*!
    \fn bool QxtBdbHash::contains ( const KEY & key ) const;

    returns true if there is a record for the specified key.
*/

/*!
    \fn bool QxtBdbHash::remove ( const KEY & key );

    removes all records with the specified key. returns true on success and false on failure.
*/

/*!
    \fn     bool QxtBdbHash::insert(KEY k, VAL v);

    inserts a record with the specified key/value combination. replaces any record with the same key.
*/

/*!
    \fn     const VAL QxtBdbHash::value (  const KEY & key  ) const;

    returns the value associated with the specified key, or a default contructed value, if no such key exists.
*/

/*!
    \fn   const VAL QxtBdbHash::operator[] ( const KEY & key ) const;

    same as value();
*/

/*!
    \fn    bool QxtBdbHash::flush();

    flushes the unerlieing DB file. all changes are synced to disk.
*/











