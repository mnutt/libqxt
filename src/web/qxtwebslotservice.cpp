/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb  module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://www.libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtwebslotservice.h"
#include "qxtwebevent.h"



QxtSlotService::QxtSlotService(QxtAbstractWebSessionManager* sm, QObject* parent):QxtAbstractWebService(sm,parent)
{
}

QUrl QxtSlotService::self(QxtWebRequestEvent* event)

{
    QStringList  u=event->url.path().split("/");
    QStringList  o=event->originalUrl.path().split("/");
    u.removeFirst();
    o.removeFirst();
    for(int i=0;i<u.count();i++)
        o.removeLast();


    QString r="/";
    foreach(QString d,o)
    {
        r+=d+"/";
    }
    return r;
}


void QxtSlotService::pageRequestedEvent(QxtWebRequestEvent* event)
{
    QList<QString> args = event->url.path().split('/');
    args.removeFirst();
    if(args.at(args.count()-1).isEmpty())
        args.removeLast();


    ///--------------find action ------------------
    QByteArray action="index";
    if(args.count())
    {
        action=args.at(0).toUtf8();
        if (action.trimmed().isEmpty())
            action="index";
        args.removeFirst();
    }



    bool ok=false;
    if (args.count()>7)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0)),
                                    Q_ARG(QString, args.at(1)),
                                    Q_ARG(QString, args.at(2)),
                                    Q_ARG(QString, args.at(3)),
                                    Q_ARG(QString, args.at(4)),
                                    Q_ARG(QString, args.at(5)),
                                    Q_ARG(QString, args.at(6)),
                                    Q_ARG(QString, args.at(7))
                                    );
    }
    else if (args.count()>6)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0)),
                                    Q_ARG(QString, args.at(1)),
                                    Q_ARG(QString, args.at(2)),
                                    Q_ARG(QString, args.at(3)),
                                    Q_ARG(QString, args.at(4)),
                                    Q_ARG(QString, args.at(5)),
                                    Q_ARG(QString, args.at(6))
                                    );
    }
    else if (args.count()>5)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0)),
                                    Q_ARG(QString, args.at(1)),
                                    Q_ARG(QString, args.at(2)),
                                    Q_ARG(QString, args.at(3)),
                                    Q_ARG(QString, args.at(4)),
                                    Q_ARG(QString, args.at(5))
                                    );
    }
    else if ( args.count()>4)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0)),
                                    Q_ARG(QString, args.at(1)),
                                    Q_ARG(QString, args.at(2)),
                                    Q_ARG(QString, args.at(3)),
                                    Q_ARG(QString, args.at(4))
                                    );
    }
    else if (args.count()>3)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0)),
                                    Q_ARG(QString, args.at(1)),
                                    Q_ARG(QString, args.at(2)),
                                    Q_ARG(QString, args.at(3))
                                    );
    }
    else if (args.count()>2)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0)),
                                    Q_ARG(QString, args.at(1)),
                                    Q_ARG(QString, args.at(2))
                                    );
    }
    else if (args.count()>1)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0)),
                                    Q_ARG(QString, args.at(1))
                                    );
    }
    else if (args.count()>0)
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event),
                                    Q_ARG(QString, args.at(0))
                                    );
    }
    else
    {
        ok=QMetaObject::invokeMethod(this, action,
                                    Q_ARG(QxtWebRequestEvent*, event)
                                    );
    }


    if(!ok)
    {
        QByteArray err="<h1>Can not find slot</h1> <pre>Class "+QByteArray(metaObject()->className ())+"\r{\npublic slots:\r    void "+action+" ( QxtWebRequestEvent* event, ";
        for(int i=0;i<args.count();i++)
            err+="QString arg"+QByteArray::number(i)+", ";
        err.chop(2);

        err+=" ); \r};\r</pre> ";

        postEvent(new QxtWebErrorEvent(event->sessionID, event->requestID, 404, err));
    }


}

void QxtSlotService::functionInvokedEvent(QxtWebRequestEvent* event) 
{
    postEvent(new QxtWebErrorEvent(event->sessionID, event->requestID, 500, "<h1>Not supported</h1>"));
}



