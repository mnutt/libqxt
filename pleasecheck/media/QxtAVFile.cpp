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


#include "QxtAVFile.h"
#include "QxtAVFile_p.h"



/**
\class QxtAVFile QxtAVFile

\ingroup media

\brief AV Decoder

A very easy to use interface for libavcodec and libavformat from ffmpeg.

*/



/*!
    Constructs a new QxtAVFile with \a parent.
 */
 QxtAVFile::QxtAVFile(QObject *parent):QObject(parent)
	{
	}
//-------------------------------------------------------------

QxtAVFile::~QxtAVFile()
	{
	qxt_d().destroy();
	}
//-------------------------------------------------------------
/*!
   opens a stream or file from  \a url.
 */
QxtError QxtAVFile::open(QString url)
	{
	return qxt_d().open(url);
	}
//-------------------------------------------------------------
/*!
this property holds the preload state

preloading is not implemented yet
*/

bool QxtAVFile::preloaded() const
	{
	return false;
	}
//-------------------------------------------------------------


QxtError QxtAVFile::setPreloaded(const bool)
	{
	QXT_DROP_OK
	}
//-------------------------------------------------------------
/*!
read an amount of \a length  shorts into the target buffer.

the result is always stereo interlaced and guarantied to be the expected size.\n
Maximum alowed length is one second. This is 1*samplerate().

*/

QxtError QxtAVFile::read(short* target, unsigned long length)
	{
	return qxt_d().read(target,length);	
	}
//-------------------------------------------------------------
/*!
read an amount of \a length  floats into the target buffer.

This is an overloaded member function, provided for convenience.
*/

QxtError QxtAVFile::read(float* target, unsigned long length)
	{
	return qxt_d().read(target,length);	
	}
//-------------------------------------------------------------
/*!
read an amount of \a length  chars into the target buffer.

This is an overloaded member function, provided for convenience.
*/

QxtError QxtAVFile::read(char * target, unsigned long length)
	{
	return qxt_d().read(target,length);	
	}
//-------------------------------------------------------------
/*!
  returns true when the end of the input stream has been reached
 */
bool 	QxtAVFile::isEof()
	{
	return qxt_d().isEof();	
	}


//-------------------------------------------------------------
/*!
  the length of the url in seconds.

that will return 0.0 if the input is a network stream
 */
double QxtAVFile::length() const
	{

	return qxt_d().length();
	}

//-------------------------------------------------------------
/*!
   seek to   \a time in seconds.


that won't do anything for network  streams.
 */
QxtError QxtAVFile::seek(double time)
	{
	return qxt_d().seek(time);
	}

//-------------------------------------------------------------
/*!
current  progress in seconds.
 */
double QxtAVFile::time() const
	{
	return qxt_d().time();
	}

//-------------------------------------------------------------

/*!
seek to   \a time in percentage.
*/

QxtError QxtAVFile::seekP(char time)
	{
	return qxt_d().seekP(time);

	}

//-------------------------------------------------------------
/*!
current progress in percentage.

returns 0 for a stream
*/

char 	QxtAVFile::timeP()   const
	{
	return qxt_d().timeP();
	}


//-------------------------------------------------------------

/*!
samplerate of the file
*/	
unsigned long QxtAVFile::samplerate() const
	{
	return qxt_d().samplerate();
	}

//-------------------------------------------------------------

/*!
set the desired samplerate. it will be automaticly resampled
*/	
QxtError QxtAVFile::setSamplerate(const unsigned long a)
	{
	return qxt_d().setSamplerate(a);
	}



