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

#ifndef QxtAVFileH
#define QxtAVFileH

#include <QThread>
#include <QString>

#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

#include <QxtCore/QxtPimpl>
#include <QxtCore/QxtError>

class QxtAVFilePrivate;
class QxtRingBuffer;
class QXT_MEDIA_EXPORT QxtAVFile : public QObject
	{
	Q_OBJECT
	Q_PROPERTY(bool preloaded READ preloaded WRITE setPreloaded);
	Q_PROPERTY(unsigned long samplerate READ samplerate WRITE setSamplerate);
	QXT_DECLARE_PRIVATE(QxtAVFile);

	public:

 		QxtAVFile(QObject *parent=0);
		~QxtAVFile();


		QxtError open(QString url);

		bool preloaded() const;
		QxtError setPreloaded(const bool);

		unsigned long samplerate() const;
		QxtError setSamplerate(const unsigned long);

		QxtError read(short*, unsigned long length);
		QxtError read(float*, unsigned long length);
		QxtError read(char *, unsigned long length);

		QxtError seek(double time);
		double 	time()   const;
		double 	length() const;

		QxtError seekP(char time);
		char 	timeP()   const;

		bool isEof();


	};

#endif

