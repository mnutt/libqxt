#include <QxtAVFile.h>
#include "QxtAudioPlayer.h"
#include <SDL/SDL.h>
#include <QDebug>





static 	SDL_AudioSpec got_spec;
static QxtAVFile * avfile=NULL;
static float * Scope=NULL;
static int FRAMES_PER_BUFFER=44800;

void QxtAudioPlayer::play(QString file)
	{
	QxtAVFile * b= avfile;
	avfile=NULL;
	if(b)delete(b);

	///intialise QxtAVFile. take care of the *2 QxtAVFile wants the amount of samples to push whereas sdl means the amount per channel
	avfile= new QxtAVFile(file,got_spec.samples*2);

	///tell avfile to resample its output to the soundcards samplerate
  	avfile->resample(got_spec.freq);	
	}

void QxtAudioPlayer::stop()
	{
	if(!avfile)return;
	QxtAVFile * b= avfile;
	avfile=NULL;
	delete(b);
	}

static void Callback (void * , Uint8 *stream, int size)
	{
	short *out = (short*)stream;
	long fliplen = size/sizeof(short);

	if(avfile)
		{
		///we could use the flip(short*) function of QxtAVFile, but since we need to process the samples anyway, we avoid overhead
		float a[fliplen];
		Q_ASSERT_X(avfile->flip(a)==fliplen,"Callback","unexpected buffersize");
		for (long i=0;i<fliplen;i++)
			{
			Q_ASSERT_X(a[1]<=1.1  &&  a[1]>=-1.1,"Callback","unhandled clipping");
			*out++=(short)(a[i]*0.99*std::numeric_limits<short>::max());
			if (i%2)Scope[i]=a[i];
			}
		}

	else
		{
		for (long i=0; i<fliplen;i++)
			{
			*out++=0;
			*out++=0; 
			Scope[i]=0.0f;
			}
		}
	}


QxtAudioPlayer::QxtAudioPlayer(QObject * parent):QObject(parent)
	{
	}


bool QxtAudioPlayer::open(int framesPerBuffer)
	{
	FRAMES_PER_BUFFER=framesPerBuffer;
	Scope=new float[FRAMES_PER_BUFFER];

	///init sdl
	Q_ASSERT_X(SDL_Init (SDL_INIT_AUDIO)>=0,"SDL",SDL_GetError());


	///sdl lets us pass a wanted spec, and it tryes to respect that. if we let it , it will try to find a mode less you intensive though
	SDL_AudioSpec wanted_spec;

	wanted_spec.freq=48000;
	wanted_spec.format=AUDIO_S16SYS;
	wanted_spec.channels=2;
        wanted_spec.silence = 0;

	wanted_spec.samples=FRAMES_PER_BUFFER;
	wanted_spec.callback=Callback;
	wanted_spec.userdata=this;
	got_spec=wanted_spec;

	///set the second parameter to NULL, to enforce the spec above, if you encounter problems
	Q_ASSERT_X(SDL_OpenAudio (&wanted_spec, &got_spec)>=0,"SDL",SDL_GetError());

	///unpause
	SDL_PauseAudio (0);
	return true;
	}


QxtAudioPlayer::~QxtAudioPlayer()
	{
	///cleanup
	SDL_CloseAudio();

	if(avfile)delete(avfile);
	if(Scope)delete [] Scope;
	}

float * QxtAudioPlayer::scope()
	{
	return Scope;
	}



