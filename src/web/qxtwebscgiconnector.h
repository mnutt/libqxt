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


#ifndef QxtWebScgiConnector_header_guards_oaksndoapsid
#define QxtWebScgiConnector_header_guards_oaksndoapsid


#include <QByteArray>
#include <QHostAddress>
#include <qxtpimpl.h>
#include "qxtwebstatelessconnector.h"

class QxtWebScgiConnectorPrivate;
class QxtWebScgiConnector : public QxtWebStatelessConnector
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtWebScgiConnector);

public:
    QxtWebScgiConnector(QObject * parent);

    virtual bool isMultiplexing()
    {
        return true;
    }
    virtual bool start (quint16 port,const QHostAddress & address);
    virtual QAbstractSocket::SocketError serverError () const;
    virtual QxtWebStatelessConnection * nextPendingConnection ();
    virtual bool hasPendingConnections () const;
    virtual bool waitForNewConnection ( int msec = 0, bool * timedOut = 0 );
};


#endif
