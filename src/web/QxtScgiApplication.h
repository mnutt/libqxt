#ifndef QScgiApplication_HEADER_GIAURX_H
#define QScgiApplication_HEADER_GIAURX_H

#include <QCoreApplication>
#include <qxtpimpl.h>
#include <QHostAddress>
#include <QxtWeb.h>

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

