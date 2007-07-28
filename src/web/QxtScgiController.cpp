#include "QxtScgiController.h"
#include <QTcpSocket>
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QUrl>

#include "QxtScgiApplication.h"


QString QxtScgiController::WebRoot()
        {
        return QCoreApplication::applicationDirPath()+"/../";
        }

 
QxtScgiController::QxtScgiController(QString name):QObject(QCoreApplication::instance())
        {
        socket_m=0;
        stream_m=0;
        setObjectName(name);
        }


QTextStream & QxtScgiController::echo()
	{
	assert(stream_m);
	return *stream_m;
	}
QTcpSocket * QxtScgiController::socket()
	{
	assert(socket_m);
	return socket_m;
	}


QString QxtScgiController::self()
	{
	return "/"+objectName();
	}


int QxtScgiController::invoke(QTcpSocket * socket,server_t & SERVER_i)
        {
        SERVER=SERVER_i;
	QList<QByteArray> args_d = SERVER["REQUEST_URI"].split('/');


        QxtWeb::readContentFromSocket(socket,SERVER,POST);





        ///--------------find action ------------------
	QByteArray action="index";	
	if (args_d.count()>2)
		{
		action=args_d.at(2);
		if (action.trimmed().isEmpty())action="index";
		}
	else if (args_d.count()>1) 
		action="index";


	if (args_d.count()>3)
                {
                args_d.removeFirst();
                args_d.removeFirst();
                args_d.removeFirst();
                }
        else
                args_d.clear();

	QStringList args;
	foreach(QByteArray arg,args_d)
		args<<QUrl::fromPercentEncoding(arg);

        QTextStream strm (socket);
        stream_m=  &strm;
        socket_m=socket;

        int retVal=666;
	if (args.count()>8)
		{
		if (!QMetaObject::invokeMethod(this, action,Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
		,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6)),Q_ARG(QString, args.at(8))))
			{
			retVal=4042;
			}
		}
	else if (args.count()>7)
		{
		if (!QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
		,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6)),Q_ARG(QString, args.at(7))
		))
			{
			retVal=4042;
			}

		}
	else if (args.count()>6)
		{
		if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
		,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6))
		))
			{
			retVal=4042;
			}
		}
	else if (args.count()>5)
		{
		if (!QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
		,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5))
		))
			{
			retVal=4042;
			}
		} 
	else if ( args.count()>4)
		{
		if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
		,Q_ARG(QString, args.at(4))
		))
			{
			retVal=4042;
			}
		} 
	else if (args.count()>3)
		{
		if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
		))
			{
			retVal=4042;
			}
		} 
	else if (args.count()>2)
		{
		if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2))
		))
			retVal=4042;
		} 
	else if (args.count()>1)
		{
		if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
		Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1))
		))
			retVal=4042;
		} 
	else if (args.count()>0)
		{
		if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,Q_ARG(QString, args.at(0))))
			retVal=4042;
		} 
	else
		{
		if ( !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ))
			{
			retVal=4042;
			}
		}

	stream_m->flush ();
        stream_m=0;
        socket_m=0;
        return retVal;
        };





