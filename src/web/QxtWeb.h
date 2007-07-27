#ifndef QxtWebHeaderGuards
#define QxtWebHeaderGuards

#include <QString>
#include <QxtError.h>
#include <QMetaType>
#include <QMap>
#include <QVariant>


typedef  QMap<QByteArray, QByteArray> server_t;
typedef  QMap<QString, QVariant> post_t;
Q_DECLARE_METATYPE(server_t)

class QTcpSocket;
class QxtWeb 
        {
        public:
                static QxtError parseString(QByteArray str, post_t & POST);
                static QxtError readContentFromSocket(QTcpSocket *,server_t &, post_t &);
        };



#endif

