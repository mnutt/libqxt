/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QxtAVPlayerGuardH
#define QxtAVPlayerGuardH


#include <QObject>
#include <QString>


#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

#include <QxtCore/QxtPimpl>
#include <QxtCore/QxtError>

class QxtAVFile;
class QxtAVPlayerPrivate;
class QXT_MEDIA_EXPORT  QxtAVPlayer : public QObject
	{
	Q_OBJECT
	Q_PROPERTY(bool peeking READ peeking WRITE setPeeking)

	QXT_DECLARE_PRIVATE(QxtAVPlayer);
	public:
		QxtAVPlayer(QObject * parent =0);
		~QxtAVPlayer();

		QxtAVFile * currentFile();

		float * peek();

		bool peeking();
		void setPeeking(bool);


	public slots:
		QxtError play      (QString url);
		QxtError pause     (bool);
		QxtError setVolume (float v);
	signals:
		void eof           ();
		void error         (QxtError);
	};



#endif


