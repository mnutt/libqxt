#ifndef QXTWEBAPPLICATION_PRIVCATE_HEADER_GIAURX_H
#define QXTWEBAPPLICATION_PRIVCATE_HEADER_GIAURX_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMap>
#include <QTextStream>
#include "QxtScgiApplication.h"
#include <QxtError.h>

//----------------------------------------------------------------------
class QxtScgiController;
class QxtScgiApplicationPrivate : public QTcpServer,public QxtPrivate<QxtScgiApplication>
	{
	Q_OBJECT
	QXT_DECLARE_PUBLIC(QxtScgiApplication);

	public:
		QxtScgiApplicationPrivate(QObject *parent = 0);
                void init();
	protected:
		void incomingConnection(int socketDescriptor);

        private:
                QxtScgiController * errorhandler;



	};


class SCGI
	{
	public:
		static QxtError header(QTcpSocket *,server_t &);
	};


#endif


