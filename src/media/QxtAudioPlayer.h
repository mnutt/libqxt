/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
#include <QObject>
#include <QString>
#include <Qxt/qxtglobal.h>


/**
\class QxtAudioPlayer QxtAudioPlayer

\ingroup media

\brief simple player using the QxtAVFile and SDL

example:
\code 
QxtAudioPlayer player;
player.play("foo.wav");
\endcode
*/

class QxtAVFile;
class QXT_MEDIA_EXPORT QxtAudioPlayer : public QObject
	{
	Q_OBJECT
	public:
		QxtAudioPlayer(QObject * parent =0);
		~QxtAudioPlayer();
		bool open(int framesPerBuffer);


		QxtAVFile * currentFile();
		float * scope();


	public slots:
		void play(QxtAVFile * file);
		void play(QString filename);
		void stop();
	signals:
		void error (QString);
	};


