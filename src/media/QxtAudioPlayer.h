/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
#include <QObject>
#include <QString>
#include <QxtAVFile.h>


/**
\class QxtAudioPlayer QxtAudioPlayer

\ingroup media

\brief simple player using the QxtAVFile and portaudio
 
sometimes you just want to play a sound in your application.
this is not meant to be a full blown media player and does not provide any functions for it.


example:
\code 
QxtAudioPlayer player;
QxtAVFile file("test.wav",&player,Qxt::preload);
player.play(&file);
\endcode
*/

class QxtAVFile;

class QxtAudioPlayer : public QObject
	{
	Q_OBJECT
	public:
		QxtAudioPlayer(QObject * parent =0);
		~QxtAudioPlayer();

	public slots:


		/**
		
		*/

		void play(QxtAVFile * file);




	private slots:
		void feof();
	};



