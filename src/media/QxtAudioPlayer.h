/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
#include <QObject>
#include <QString>


/**
\class QxtAudioPlayer QxtAudioPlayer

\ingroup media

\brief simple player using the QxtAVFile and portaudio
 
sometimes you just want to play a sound in your application.
this is not meant to be a full blown media player and does not provide any functions for it.
*/



class QxtAudioPlayerStaticEofObjectHolder: public QObject
	{
	Q_OBJECT
	public slots:
		void f__eof();
	};



class QxtAudioPlayer : public QObject
	{
	Q_OBJECT
	public:
		QxtAudioPlayer(QObject * parent =0);
		~QxtAudioPlayer();

	public slots:

		/**
		usage:

		\code
		QxtAudioPlayer::play("sound/ding.wav");
		\endcode
		obviously you do not need to construct an object

		calling this slot while another file is playing will interupt the current playback
		*/

		static void play(QString url);
	

		/**
		if you do not need sound a longer time, you should close the sound out.
		It will automaticly be reopened the next play();
		*/
		static void close();


	};



