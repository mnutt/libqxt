#include <db.h>

#if DB_VERSION_MAJOR < 4
#error db>=4.4 required
#endif

#if DB_VERSION_MAJOR < 5

#if DB_VERSION_MINOR < 4
#error db>=4.4 required
#endif

#if DB_VERSION_MINOR < 6
#warning db < 4.6, some features will be disabled
#endif

#endif

int main (int,char**)
{
    DB * db;
    db_create(&db, NULL, 0);
    return 0;
}


