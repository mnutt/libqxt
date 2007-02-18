/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
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
		unsigned long available	();
		unsigned long write	(char * source, unsigned long size);
	};

#endif
