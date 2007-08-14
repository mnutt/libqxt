#ifndef QxtHash_H_GUARD
#define QxtHash_H_GUARD

#include <QByteArray>
#include <qxtglobal.h>
#include "qxtpimpl.h"

class QxtHashPrivate;
class QXT_CRYPTO_EXPORT QxtHash
	{
	QXT_DECLARE_PRIVATE(QxtHash);
	public:
		enum Algorithm 
			{
			Md5,
			Md4
			};
		QxtHash (Algorithm);
		QxtHash (Algorithm, const QByteArray & );

		void append ( const QByteArray & );
		void operator+= ( const QByteArray &);

		void reset();

		QByteArray hash();
	};

#endif
