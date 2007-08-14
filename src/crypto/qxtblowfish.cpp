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


#include "qxtblowfish.h"
#include <openssl/blowfish.h>


static 	BF_KEY * key;   ///FIXME: holy crap, what am i doing here?!




/**
\class QxtBlowFish QxtBlowFish

\ingroup network

\brief  Blowfish Encryption Class
 

useage:
\code
QxtBlowFish() fish;
fish.setPassword("foobar").

QByteArray a("barblah");

a= fish.encrypt(a);
a= fish.decrypt(a);
\endcode
*/





QxtBlowFish::QxtBlowFish(QObject * parent) :QObject(parent)
	{
	key=new BF_KEY;
	}


void QxtBlowFish::setPassword(QByteArray k ) 
	{
	BF_set_key(key, k.count() , (unsigned char *)k.constData ());
	}



QByteArray  QxtBlowFish::encrypt(QByteArray in)
	{
	QByteArray out(in);
	int num =0;
	unsigned char  ivec [8];
	ivec[0]=(unsigned char )3887;
	ivec[1]=(unsigned char )3432;
	ivec[2]=(unsigned char )3887;
	ivec[3]=(unsigned char )2344;
	ivec[4]=(unsigned char )678;
	ivec[5]=(unsigned char )3887;
	ivec[6]=(unsigned char )575;
	ivec[7]=(unsigned char )2344;
	ivec[8]=(unsigned char )2222;


	BF_cfb64_encrypt(
		(unsigned char *)in.constData (),
		(unsigned char *)out.data(),
                in.size(),
		key,
		ivec,
		&num,
                BF_ENCRYPT
		);


	out=out.toBase64();
	return out;

	}


QByteArray  QxtBlowFish::decrypt(QByteArray in)

	{
	in=QByteArray::fromBase64(in);
	
	QByteArray out(in);
	
	int num =0;
	unsigned char  ivec [8];
	ivec[0]=(unsigned char )3887;
	ivec[1]=(unsigned char )3432;
	ivec[2]=(unsigned char )3887;
	ivec[3]=(unsigned char )2344;
	ivec[4]=(unsigned char )678;
	ivec[5]=(unsigned char )3887;
	ivec[6]=(unsigned char )575;
	ivec[7]=(unsigned char )2344;
	ivec[8]=(unsigned char )2222;
	
	
	BF_cfb64_encrypt(
		(unsigned char *)in.constData (),
		(unsigned char *)out.data(),
                in.size(),
		key,
		ivec,
		&num,
		BF_DECRYPT
		);


	return out;
	}
