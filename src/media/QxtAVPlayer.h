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

#ifndef QxtAVPlayerGuardH
#define QxtAVPlayerGuardH


#include <QObject>
#include <QString>


#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

#include <QxtCore/QxtPimpl>
#include <QxtCore/QxtError>

class QxtAVFile;
class QxtAVPlayerPrivate;
class QXT_MEDIA_EXPORT  QxtAVPlayer : public QObject
	{
	Q_OBJECT
	Q_PROPERTY(bool peeking READ peeking WRITE setPeeking)

	QXT_DECLARE_PRIVATE(QxtAVPlayer);
	public:
		QxtAVPlayer(QObject * parent =0);
		~QxtAVPlayer();

		QxtAVFile * currentFile();

		float * peek();

		bool peeking();
		void setPeeking(bool);


	public slots:
		QxtError play      (QString url);
		QxtError pause     (bool);
		QxtError setVolume (float v);
	signals:
		void eof           ();
		void error         (QxtError);
	};



#endif


