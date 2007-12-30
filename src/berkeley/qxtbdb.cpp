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
#include <QFileInfo>


/*!
    \class QxtBdb QxtBdb
    \ingroup QxtBerkeley
    \brief base class for low level Berkeley DB access

*/


/*!
    \fn bool QxtBdb::open(QString path,OpenFlags f=0)

    opens the specified file. returns true on success and false on failure. \n Note that a sanity check is performed before opening the file.
*/


/*!
    \fn bool OpenFlags QxtBdb::openFlags();

    returns the open flags
*/

/*!
    \fn bool QxtBdb::flush();

    flushes the DB file. all changes are synced to disk.
*/

/*!
    \fn     BerkeleyDB::DB * QxtBdb::db;

    public access to the BD C Api structure
*/







static void qxtBDBDatabaseErrorHandler(const  BerkeleyDB::DB_ENV*, const char* a, const char* b)
{
    qDebug("QxtBDBDatabase: %s, %s",a,b);
}


QxtBdb::QxtBdb()
{
    Q_ASSERT_X(db_create(&db, NULL, 0)==0,Q_FUNC_INFO,"db_create failed");
    db->set_errcall(db, qxtBDBDatabaseErrorHandler);
}
QxtBdb::~QxtBdb()
{
    db->close(db, 0);
}




bool QxtBdb::open(QString path,OpenFlags f)
{

    if(QFileInfo(path).exists ())
    {

        BerkeleyDB::DB * tdb;
        Q_ASSERT_X(db_create(&tdb, NULL, 0)==0,Q_FUNC_INFO,"db_create failed");

        if(tdb->verify(tdb, qPrintable(path), NULL, NULL,NULL)==DB_VERIFY_BAD)
            qCritical("QxtBdb::open Database '%s' is corrupted.",qPrintable(path));
    }



    int flags=0;
    if (f&CreateDatabase)
        flags|=DB_CREATE;

    if (f&ReadOnly)
        flags|=DB_RDONLY;

    return (db->open(db,        /* DB structure pointer */
                NULL,       /* Transaction pointer */
                qPrintable(path), /* On-disk file that holds the database. */
                NULL,       /* Optional logical database name */
                BerkeleyDB::DB_BTREE,   /* Database access method */
                flags,  /* Open flags */
                0)
        ==0);



}


QxtBdb::OpenFlags QxtBdb::openFlags()
{
    OpenFlags f;

    u_int32_t open_flags;
    db->get_open_flags(db, &open_flags); 



    if(open_flags&DB_CREATE)
        f|=CreateDatabase;
    if(open_flags&DB_RDONLY)
        f|=ReadOnly;

    return f;
}




bool QxtBdb::flush()
{
    return (db->sync(db,0)==0);
}




