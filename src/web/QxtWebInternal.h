/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/
#include <QString>
#include <QHash>

class QTcpSocket;
class QTextStream;
class QxtWebInternal
	{
	public:
		static void internalPage (int code,QString description,QTcpSocket *, QHash<QByteArray, QByteArray>  * SERVER=0,QString hint=QString());
		static void internalPage (int code,QString description,QTextStream &  stream, QHash<QByteArray, QByteArray>  * SERVER=0,QString hint=QString());
		static QString toHtml (QString text);
		static QString WebRoot();

	private:
		static bool internalPage_p (int code,QString description,QTextStream &  stream, QHash<QByteArray, QByteArray>  * SERVER=0,QString hint=QString());
	};



