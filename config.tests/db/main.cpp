#include <db.h>

#if DB_VERSION_MAJOR < 4
#error db>=4.4 required
#endif

#if DB_VERSION_MINOR < 4
#error db>=4.4 required
#endif


int main (int,char**)
{
    DB * db;
    db_create(&db, NULL, 0);
    return 0;
}


