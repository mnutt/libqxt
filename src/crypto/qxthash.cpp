#include "qxthash.h"
#include "qxthash_p.h"

QxtHash::QxtHash (Algorithm algo)
	{
	QXT_INIT_PRIVATE(QxtHash);
	qxt_d().algo=algo;
	reset();
	}
QxtHash::QxtHash (Algorithm algo, const QByteArray & data)
	{
	QXT_INIT_PRIVATE(QxtHash);
	qxt_d().algo=algo;
	reset();
	append(data);
	}

void QxtHash::append ( const QByteArray & dt)
	{
	if (qxt_d().algo==Md5)
		{
		MD5Update(&qxt_d().md5ctx, (const unsigned char *)dt.constData(), dt.length());
		}
	else if (qxt_d().algo==Md4)
		{
		md4_update(&qxt_d().md4ctx, (const unsigned char *)dt.constData(), dt.length());
		}

	}

void  QxtHash::operator+= ( const QByteArray & dt)
	{
	append(dt);
	}

void QxtHash::reset()
	{
	if (qxt_d().algo==Md5)
		{
		MD5Init(&qxt_d().md5ctx);
		}
	else if (qxt_d().algo==Md4)
		{
		md4_init(&qxt_d().md4ctx);
		}
	}

QByteArray QxtHash::hash()
	{
	QByteArray hs;

	if (qxt_d().algo==Md5)
		{
		hs.resize(16);
		MD5Final(&qxt_d().md5ctx, (unsigned char *)hs.data());
		}
	else if (qxt_d().algo==Md4)
		{
		hs.resize(MD4_RESULTLEN);
		md4_final(&qxt_d().md4ctx, (unsigned char *)hs.data());
		}

	return hs;
	}


///uh oh
#include "thirdparty/md5.cpp"
#include "thirdparty/md4.cpp"


