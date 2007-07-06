#include "QxtScgiController.h"
#include <QTcpSocket>
#include <QStringList>
#include <QDebug>

#include "QxtScgiApplication.h"


QxtScgiController::QxtScgiController(QString name,QxtScgiApplication *parent):QObject(parent)
        {
        stream_m=0;
        setObjectName(name);
        }

int QxtScgiController::invoke(QTcpSocket * socket,server_t & SERVER_i)
        {
        SERVER=SERVER_i;
	QList<QByteArray> args = SERVER["REQUEST_URI"].split('/');


        ///--------------find action ------------------
	QByteArray action="index";	
	if (args.count()>2)
		{
		action=args.at(2);
		if (action.trimmed().isEmpty())action="index";
		}
	else if (args.count()>1) 
		action="index";


	if (args.count()>3)
                {
                args.removeFirst();
                args.removeFirst();
                args.removeFirst();
                }
        else
                args.clear();



        QTextStream strm (socket);
        stream_m=  &strm;




        /**
        since the meta object passes the method information all wrong we need to try and error
        if int index(foo,foo,foo) doesnt exist, we try index(foo,foo,foo,"") and so on
        if that doesnt work it tryes foo,foo and foo
        **/
        ///TODO  so ugly :/

        int retVal=666;
        bool up=true;


        bool tryed[9]={false,false,false,false,false,false,false,false,false};

        forever
                {
                qDebug()<<"invoke"<<action<<args.count();
                if (args.count()>8)
                        {
                        if (tryed[9] || !QMetaObject::invokeMethod(this, action,Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                        ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6)),Q_ARG(QString, args.at(8))))
                                {
                                tryed[9]=true;
                                up=false;
                                args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        }
                else if (args.count()>7)
                        {
                        if (tryed[8] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                        ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6)),Q_ARG(QString, args.at(7))
                        ))
                                {
                                tryed[8]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        }
                else if (args.count()>6)
                        {
                        if (tryed[7] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                        ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5)),Q_ARG(QString, args.at(6))
                        ))
                                {
                                tryed[7]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        }
                else if (args.count()>5)
                        {
                        if (tryed[6] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                        ,Q_ARG(QString, args.at(4)),Q_ARG(QString, args.at(5))
                        ))
                                {
                                tryed[6]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        } 
                else if ( args.count()>4)
                        {
                        if (tryed[5] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                        ,Q_ARG(QString, args.at(4))
                        ))
                                {
                                tryed[5]=true;
                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        } 
                else if (args.count()>3)
                        {
                        if (tryed[4] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2)),Q_ARG(QString, args.at(3))
                        ))
                                {
                                tryed[4]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        } 
                else if (args.count()>2)
                        {
                        if (tryed[3] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1)),Q_ARG(QString, args.at(2))
                        ))

                                {
                                tryed[3]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        } 
                else if (args.count()>1)
                        {
                        if (tryed[2] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,
                        Q_ARG(QString, args.at(0)),Q_ARG(QString, args.at(1))
                        ))

                                {
                                tryed[2]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        } 
                else if (args.count()>0)
                        {
                        if (tryed[1] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ,Q_ARG(QString, args.at(0))))

                                {
                                tryed[1]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        args.removeLast();
                                continue;
                                }
                        else 
                                break;
                        } 
                else
                        {
                        if (tryed[0] || !QMetaObject::invokeMethod(this, (action),Q_RETURN_ARG(int, retVal) ))
                                {
                                tryed[0]=true;

                                if(up)
                                        args<<QByteArray();
                                else
                                        return 4042; ///TODO X-REDIRECT
                                continue;
                                }
                        else 
                                break;
                        } 
                }

	stream_m->flush ();
        stream_m=0;

        return retVal;
        };





