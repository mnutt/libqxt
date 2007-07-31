#ifndef QxtStdin_H_GUARD
#define QxtStdin_H_GUARD
#include <qxtglobal.h>
#include <QIODevice>
#include <QQueue>

class QSocketNotifier;
class QXT_CORE_EXPORT QxtStdio : public QIODevice
	{
	Q_OBJECT
	public:
		QxtStdio(QObject * parent=0);
		virtual bool isSequential () const;
		virtual qint64 bytesAvailable () const;
	protected:
		virtual qint64 readData ( char * data, qint64 maxSize );
		virtual qint64 writeData ( const char * data, qint64 maxSize );
	private:
		QSocketNotifier * notify;
		QQueue<char> inbuffer;
	private slots:	
		void activated(int );

	};
#endif
