#include "QxtAVPlayer.h"
#include <SDL/SDL.h>

class QxtAVPlayerPrivate : public QObject, public QxtPrivate<QxtAVPlayer>
	{
	Q_OBJECT
	QXT_DECLARE_PUBLIC(QxtAVPlayer);	
	public:
		QxtAVPlayerPrivate();
		
		SDL_AudioSpec 	got_spec;
		QxtAVFile * 	avfile;
		unsigned long samplerate;
		float volume_m;
		QxtError setVolume (float v);


		bool opened_m;


		QxtError play(QString file);

		QxtError pause     (bool);


		void up_fetch_eof()
			{emit(eof());}


		bool peeking;


		float * peek;


	public slots:
		QxtError open();
		QxtError close();	
	signals:
		void eof           ();
	};







