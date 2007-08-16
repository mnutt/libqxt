#ifndef QxtStdStreambufDevice_HEADER_GUARD
#define QxtStdStreambufDevice_HEADER_GUARD

#include <QIODevice>
#include <QObject>
#include <iostream>
class QxtStdStreambufDevice : public QIODevice
	{
	Q_OBJECT
	public:
		QxtStdStreambufDevice(std::streambuf *,QObject * parent=0); /// one rw device
		QxtStdStreambufDevice(std::streambuf * r,std::streambuf * w,QObject * parent=0); ///one for read and one for write

		virtual bool isSequential () const;
		virtual qint64 bytesAvailable () const;
	protected:
		virtual qint64 readData ( char * data, qint64 maxSize );
		virtual qint64 writeData ( const char * data, qint64 maxSize );


        private:
                std::streambuf * buff;
                std::streambuf * buff_w;

	};

#endif
