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
	QXT_DECLARE_PRIVATE(QxtAVPlayer);
	public:
		QxtAVPlayer(QObject * parent =0);
		~QxtAVPlayer();

		QxtAVFile * currentFile();

	public slots:
		QxtError play      (QString url);
		QxtError pause     (bool);
		QxtError setVolume (float v);
	signals:
		void eof           ();
		void error         (QxtError);
	};



#endif


