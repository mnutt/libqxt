/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
#ifndef ___BLOWFISH_H___
#define ___BLOWFISH_H___

#include <QByteArray>
#include <QObject>
#include <Qxt/qxtglobal.h>


class QXT_NETWORK_EXPORT QxtBlowFish : public QObject
{
	Q_OBJECT
	
	public:
		QxtBlowFish(QObject * parent = 0);
		void setPassword(QByteArray);
		QByteArray encrypt(QByteArray);
		QByteArray decrypt(QByteArray);

};


#endif


