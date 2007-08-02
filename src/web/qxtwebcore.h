/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#ifndef QxtWebCore_HEADER_GIAURX_H
#define QxtWebCore_HEADER_GIAURX_H

#include <QObject>
#include <QMap>
#include <QMetaType>
#include <qxtpimpl.h>
#include <qxterror.h>
#include <qxtrpcpeer.h>
#include <qxtglobal.h>

typedef  QMap<QByteArray, QByteArray> server_t;
typedef  QMap<QString, QVariant> post_t;


Q_DECLARE_METATYPE(server_t)

class QxtWebCorePrivate;
class QXT_WEB_EXPORT QxtWebCore: public QObject
	{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtWebCore);
	public:
                QxtWebCore ();
                ~QxtWebCore ();
                static QxtWebCore* instance();
                static void send(QByteArray);
                static void header(QByteArray,QByteArray);
                static server_t & SERVER();


                /*helper*/
                static QxtError parseString(QByteArray str, post_t & POST);
//                 static QxtError readContentFromSocket(QTcpSocket *,server_t &, post_t &);

        protected:
                 static QxtRPCPeer * peer();


        signals:
                void request();

	};



#endif


