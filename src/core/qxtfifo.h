#ifndef QxtFifo_H_GUARD
#define QxtFifo_H_GUARD
#include <qxtglobal.h>
#include <QIODevice>
#include <QQueue>

class QXT_CORE_EXPORT QxtFifo : public QIODevice
	{
	Q_OBJECT
	public:
		QxtFifo(QObject * parent=0);

		virtual bool isSequential () const;
		virtual qint64 bytesAvailable () const;
	protected:
		virtual qint64 readData ( char * data, qint64 maxSize );
		virtual qint64 writeData ( const char * data, qint64 maxSize );


	private:
		QQueue<char>  q;
	};

#endif

