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
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#ifndef QxtWebLegacyEngine_HEADER_GIAURX_H
#define QxtWebLegacyEngine_HEADER_GIAURX_H

#include <QObject>
#include <QMap>


#include <qxtglobal.h>
#include <qxtwebstatelessconnector.h>




class QTextCodec;
class QxtWebLegacyEnginePrivate;
class QXT_WEB_EXPORT QxtWebLegacyEngine: public QObject
{
    Q_OBJECT
public:
    QxtWebLegacyEngine (QxtWebStatelessConnector *);
    ~QxtWebLegacyEngine ();


    static void send(QString);
    static void close();
    static void header(QString,QString);

    static QHttpRequestHeader & SERVER();
    static QIODevice * socket();

    static void redirect(QString location,int code=303);




    static QxtWebLegacyEngine * instance();
    static QByteArray content(int maxsize=5000);

private slots:
    void incomming();
signals:
    void request();

private:
    QxtWebStatelessConnector  * sc;
    QxtWebStatelessConnection * cc;

};



#endif


