/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QxtAVFileH
#define QxtAVFileH

#include <QThread>
#include <QString>

#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

#include <QxtCore/QxtPimpl>
#include <QxtCore/QxtError>

class QxtAVFilePrivate;
class QxtRingBuffer;
class QXT_MEDIA_EXPORT QxtAVFile : public QObject
	{
	Q_OBJECT
	Q_PROPERTY(bool preloaded READ preloaded WRITE setPreloaded);
	Q_PROPERTY(unsigned long samplerate READ samplerate WRITE setSamplerate);
	QXT_DECLARE_PRIVATE(QxtAVFile);

	public:

 		QxtAVFile(QObject *parent=0);
		~QxtAVFile();


		QxtError open(QString url);

		bool preloaded() const;
		QxtError setPreloaded(const bool);

		unsigned long samplerate() const;
		QxtError setSamplerate(const unsigned long);

		QxtError read(short*, unsigned long length);
		QxtError read(float*, unsigned long length);
		QxtError read(char *, unsigned long length);

		QxtError seek(double time);
		double 	time()   const;
		double 	length() const;

		QxtError seekP(char time);
		char 	timeP()   const;

		bool isEof();


	};

#endif

