#include "qxtbdb.h"
#include <QFileInfo>

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




