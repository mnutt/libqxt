/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtBlowFish.h"


QxtBlowFish::QxtBlowFish(QObject * parent) :QObject(parent)
{}


void QxtBlowFish::setPassword(QByteArray k ) 
	{
	BF_set_key(&key, k.count() , (unsigned char *)k.constData ());
	}



QByteArray  QxtBlowFish::encrypt(QByteArray in)
	{
	QByteArray out(in);
	int num =0;
	unsigned char  ivec [8];
	ivec[0]=3887;
	ivec[1]=3432;
	ivec[2]=3887;
	ivec[3]=2344;
	ivec[4]=678;
	ivec[5]=3887;
	ivec[6]=575;
	ivec[7]=2344;
	ivec[8]=2222;


	BF_cfb64_encrypt(
		(unsigned char *)in.constData (),
		(unsigned char *)out.data(),
                in.size(),
		&key,
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
	ivec[0]=3887;
	ivec[1]=3432;
	ivec[2]=3887;
	ivec[3]=2344;
	ivec[4]=678;
	ivec[5]=3887;
	ivec[6]=575;
	ivec[7]=2344;
	ivec[8]=2222;
	
	
	BF_cfb64_encrypt(
		(unsigned char *)in.constData (),
		(unsigned char *)out.data(),
                in.size(),
		&key,
		ivec,
		&num,
		BF_DECRYPT
		);


	return out;
	}
