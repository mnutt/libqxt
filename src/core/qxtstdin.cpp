#include "qxtstdin.h" 
#include <cstdio>
#include <QSocketNotifier>

/**
\class QxtStdin QxtStdin

\ingroup core

\brief QIODevice support for stdin

including readyRead() signal
note that when using this class, the buffer for stdin will be disabled, and NOT reenabled on destruction
*/
QxtStdin::QxtStdin(QObject * parent):QxtFifo(parent)
	{
	setvbuf ( stdin , NULL , _IONBF , 0 );
	setOpenMode (QIODevice::ReadOnly);
	notify = new QSocketNotifier ( fileno(stdin),QSocketNotifier::Read,this );
	connect(notify, SIGNAL(activated(int)),this,SLOT(activated(int)));
	}

void QxtStdin::activated(int )	
	{
	char c=getchar();
	writeData (&c,1);
	}


