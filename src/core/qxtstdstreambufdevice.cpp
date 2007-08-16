#include "qxtstdstreambufdevice.h"

QxtStdStreambufDevice::QxtStdStreambufDevice(std::streambuf * b,QObject * parent):QIODevice(parent),buff(b)
        {
	setOpenMode (QIODevice::ReadWrite); ///we don't know the real state
        }

bool QxtStdStreambufDevice::isSequential() const
        {
        return true;///for now
        }

qint64 QxtStdStreambufDevice::bytesAvailable () const
        {
        return buff->in_avail();
        }
qint64 QxtStdStreambufDevice::readData ( char * data, qint64 maxSize )
        {
        return buff->sgetn(data,maxSize);
        }

qint64 QxtStdStreambufDevice::writeData ( const char * data, qint64 maxSize )
        {
        return buff->sputn(data,maxSize);
        }
