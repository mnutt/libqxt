#ifndef QxtBdb_H_kpasd
#define QxtBdb_H_kpasd

#include <QFlags>
#include <QString>




///its impossible to forward anyway,
namespace BerkeleyDB
{
    extern "C"
    {
        #include <db.h>
    }

}

class QxtBdb
{
public:
    enum OpenFlag
    {
        CreateDatabase  =0x1,
        ReadOnly        =0x2
    };
    Q_DECLARE_FLAGS(OpenFlags, OpenFlag);

    QxtBdb();
    ~QxtBdb();

    bool open(QString path,OpenFlags f=0);

    OpenFlags openFlags();

    bool flush();



    BerkeleyDB::DB * db;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(QxtBdb::OpenFlags);





#endif
