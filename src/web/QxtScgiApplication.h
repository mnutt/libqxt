#ifndef QScgiApplication_HEADER_GIAURX_H
#define QScgiApplication_HEADER_GIAURX_H

#include <QCoreApplication>
#include <QxtPimpl.h>
#include <QHostAddress>
#include <QMetaType>
#include <QxtError.h>
#include <QMap>

typedef  QMap<QByteArray, QByteArray> server_t;
Q_DECLARE_METATYPE(server_t)

class QxtScgiApplicationPrivate;
class QxtScgiApplication: public QCoreApplication
	{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtScgiApplication);
	public:
                QxtScgiApplication ( int & argc, char ** argv );
                int exec (quint16 port = 8000,const QHostAddress & address = QHostAddress::LocalHost);
	};








#endif

