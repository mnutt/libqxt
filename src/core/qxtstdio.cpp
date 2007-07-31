#include "qxtstdio.h" 
#include <cstdio>
#include <QSocketNotifier>

/**
\class QxtStdio QxtStdio

\ingroup core

\brief QIODevice support for stdin and stdout

including readyRead() signal
note that when using this class, the buffers for stdin/stdout will be disabled, and NOT reenabled on destruction

perfect as a counter part for QProcess
*/

QxtStdio::QxtStdio(QObject * parent):QIODevice(parent)
	{
	setvbuf ( stdin , NULL , _IONBF , 0 );
	setvbuf ( stdout , NULL , _IONBF , 0 );

	setOpenMode (QIODevice::ReadWrite);
	notify = new QSocketNotifier ( fileno(stdin),QSocketNotifier::Read,this );
	connect(notify, SIGNAL(activated(int)),this,SLOT(activated(int)));
	}

qint64 QxtStdio::readData ( char * data, qint64 maxSize )
	{
	qint64 i=0;
	for (;i<maxSize;i++)
		{
		if (inbuffer.isEmpty())
			break;
		(*data++)=inbuffer.dequeue();
		}
	return i;
	}
qint64 QxtStdio::writeData ( const char * data, qint64 maxSize )
	{
	qint64 i=0;
	for (;i<maxSize;i++)
		{
		char c=*data++;
		putchar(c);

///FIXME: why the heck is that not working... the C99 standard says it should...
// 		if (putchar(c)!=c)		
// 			break;


		}
// 	emit(bytesWritten (i)); ///FIXME: acording to the docs this may not be recoursive. how do i prevent that?
	return i;
	}


bool QxtStdio::isSequential () const
	{
	return true;
	}


qint64 QxtStdio::bytesAvailable () const
	{
	return inbuffer.count();
	}

void QxtStdio::activated(int )	
	{
	inbuffer.enqueue(getchar());
 	emit(readyRead ());
	}


