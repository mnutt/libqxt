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
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/

#ifndef  HEADER_GUARD_QxtRingBuffer
#define  HEADER_GUARD_QxtRingBuffer
#include <QObject>
#include <QxtCore/QxtPimpl>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

class QxtRingBufferPrivate;
class QXT_MEDIA_EXPORT QxtRingBuffer : public QObject
	{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtRingBuffer);

	public:
		QxtRingBuffer	(unsigned long size, QObject * parent=0);
		 ~QxtRingBuffer	();

		unsigned long read	(char * destination, unsigned long size);
		unsigned long peek	(char * destination, unsigned long size);
		unsigned long available	();
		unsigned long write	(char * source, unsigned long size);

		void get_read_vector    (char  **buffer,unsigned long * length);
		void read_advance       (unsigned long length);

		void get_write_vector   (char  **buffer,unsigned long * length);
		void write_advance      (unsigned long length);

  
	};

#endif
