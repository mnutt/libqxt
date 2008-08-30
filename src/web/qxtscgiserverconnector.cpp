/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb  module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
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

/**
\class QxtScgiServerConnector QxtScgiServerConnector

\ingroup QxtWeb

\brief An SCGI connector for QxtHttpSessionManager


QxtScgiServerConnector implements the SCGI protocoll supported by almost all modern web servers.



\sa QxtHttpSessionManager
*/
#include "qxthttpsessionmanager.h"
#include "qxtwebevent.h"
#include <QTcpServer>
#include <QHash>
#include <QTcpSocket>
#include <QString>

#ifndef QXT_DOXYGEN_RUN
class QxtScgiServerConnectorPrivate : public QxtPrivate<QxtScgiServerConnector>
{
public:
    QTcpServer* server;
};
#endif

/**
 * Creates a QxtHttpServerConnector with the given parent.
 */
QxtScgiServerConnector::QxtScgiServerConnector(QObject* parent) : QxtAbstractHttpConnector(parent)
{
    QXT_INIT_PRIVATE(QxtScgiServerConnector);
    qxt_d().server = new QTcpServer(this);
    QObject::connect(qxt_d().server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

/**
 * \reimp
 */
bool QxtScgiServerConnector::listen(const QHostAddress& interface, quint16 port)
{
    return qxt_d().server->listen(interface, port);
}

/**
 * \priv
 */
void QxtScgiServerConnector::acceptConnection()
{
    QTcpSocket* socket = qxt_d().server->nextPendingConnection();
    addConnection(socket);
}

/**
 * \reimp
 */
bool QxtScgiServerConnector::canParseRequest(const QByteArray& buffer)
{
    if (buffer.size() < 10)
        return false;
    QString expectedsize;
    for (int i = 0;i < 10;i++)
    {
        if (buffer.at(i) == ':')
        {
            break;
        }
        else
        {
            expectedsize += buffer.at(i);
        }
    }

    if (expectedsize.isEmpty())
    {
        //protocoll error
        return false;
    }

    return (buffer.size() > expectedsize.toInt());
}

/**
 * \reimp
 */
QHttpRequestHeader QxtScgiServerConnector::parseRequest(QByteArray& buffer)
{
    QString expectedsize_s;
    for (int i = 0;i < 20;i++)
    {
        if (buffer.at(i) == ':')
        {
            break;
        }
        else
        {
            expectedsize_s += buffer.at(i);
        }
    }

    if (expectedsize_s.isEmpty())
    {
        //protocoll error
        return QHttpRequestHeader();
    }


    buffer = buffer.right(buffer.size() - (expectedsize_s.count() + 1));


    QHttpRequestHeader request_m;

    QByteArray name;
    int i = 0;
    while ((i = buffer.indexOf('\0')) > -1)
    {
        if (name == "")
        {
            name = buffer.left(i);
        }
        else
        {
            request_m.setValue(QString::fromAscii(name).toLower(), QString::fromAscii(buffer.left(i)));
            name = "";
        }
        buffer = buffer.mid(i + 1);
    }


    request_m.setRequest(request_m.value("request_method"), request_m.value("request_uri"), 1, 0);


    foreach(QString key, request_m.keys())
    {
        if (key.startsWith("http_"))
        {
            request_m.setValue(key.right(key.size() - 5), request_m.value(key));
        }
    }

    request_m.setValue("Connection", "close");


    buffer.chop(1);


    return request_m;
}

/**
 * \reimp
 */
void QxtScgiServerConnector::writeHeaders(QIODevice* device, const QHttpResponseHeader& response_m)
{

    device->write(("Status:" + QString::number(response_m.statusCode()) + " " + response_m.reasonPhrase() + "\r\n").toAscii());

    foreach(QString key, response_m.keys())
    {
        device->write((key + ":" + response_m.value(key) + "\r\n").toAscii());
    }
    device->write("\r\n");
}
