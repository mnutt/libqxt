#include "QxtAVFile.h"
#include "QxtAVFile_p.h"




 QxtAVFile::QxtAVFile(QObject *parent):QObject(parent)
	{
	}
//-------------------------------------------------------------

QxtAVFile::~QxtAVFile()
	{
	qxt_d().destroy();
	}
//-------------------------------------------------------------

QxtError QxtAVFile::open(QString url)
	{
	return qxt_d().open(url);
	}
//-------------------------------------------------------------

bool QxtAVFile::preloaded() const
	{
	return false;
	}
//-------------------------------------------------------------

QxtError QxtAVFile::setPreloaded(const bool)
	{
	QXT_DROP_OK
	}
//-------------------------------------------------------------

QxtError QxtAVFile::read(short* target, unsigned long length)
	{
	return qxt_d().read(target,length);	
	}
//-------------------------------------------------------------

QxtError QxtAVFile::read(float* target, unsigned long length)
	{
	return qxt_d().read(target,length);	
	}
//-------------------------------------------------------------

QxtError QxtAVFile::read(char * target, unsigned long length)
	{
	return qxt_d().read(target,length);	
	}
//-------------------------------------------------------------

bool 	QxtAVFile::isEof()
	{
	return qxt_d().isEof();	
	}


//-------------------------------------------------------------

double QxtAVFile::length() const
	{
	return qxt_d().length();
	}

//-------------------------------------------------------------

QxtError QxtAVFile::seek(double time)
	{
	return qxt_d().seek(time);
	}

//-------------------------------------------------------------

double QxtAVFile::time() const
	{
	return qxt_d().time();
	}

//-------------------------------------------------------------


QxtError QxtAVFile::seekP(char time)
	{
	return qxt_d().seekP(time);

	}

//-------------------------------------------------------------
char 	QxtAVFile::timeP()   const
	{
	return qxt_d().timeP();
	}


//-------------------------------------------------------------
	
unsigned long QxtAVFile::samplerate()
	{
	return qxt_d().samplerate();
	}


