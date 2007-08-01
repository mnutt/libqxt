#ifndef QxtWebCore_HEADER_GIAURX_H
#define QxtWebCore_HEADER_GIAURX_H

#include <QObject>
#include <QMap>
#include <QMetaType>
#include <qxtpimpl.h>
#include <qxterror.h>
#include <qxtrpcpeer.h>

typedef  QMap<QByteArray, QByteArray> server_t;
typedef  QMap<QString, QVariant> post_t;


Q_DECLARE_METATYPE(server_t)

class QxtWebCorePrivate;
class QxtWebCore: public QObject
	{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtWebCore);
	public:
                QxtWebCore ();
                static QxtWebCore* instance();
                static void send(QByteArray);


                static QxtRPCPeer * peer();

                /*helper*/
                static QxtError parseString(QByteArray str, post_t & POST);
//                 static QxtError readContentFromSocket(QTcpSocket *,server_t &, post_t &);

	};



#endif


