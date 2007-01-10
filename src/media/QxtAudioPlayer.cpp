/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
#include "QxtAudioPlayer.h"
#include <portaudio.h>
#include <QCoreApplication>
#include <QxtAVFile.h>

#define FRAMES_PER_BUFFER   1024


static	QxtAVFile * avfile=NULL;


/*!
Portaudio will decide itself when to call this function. it expects to get 'frames' numbers of frames * channels  to be pushed to out. interleaved
This function allowes us to pass around a pointer to any object we like. we'll store our object pointer in it
*/
static int PortaudioCallback(const void *, void *outputBuffer,unsigned long framerate,const PaStreamCallbackTimeInfo* ,PaStreamCallbackFlags ,void * )
	{
	///prepare the buffer
	float *out = (float*)outputBuffer;

	///if there is no avfile we will pass silence
	if (!avfile)
		{
		for (unsigned long i=0;i<framerate;i++)
			*out++=0.0f;
		return paContinue;
		}

	///flip the data to portaudios callback buffer
	avfile->flip(out);

	return paContinue;
	}





class AUDIOOUT
{
public:
	AUDIOOUT()
		{
		///init portaudio
		Q_ASSERT(Pa_Initialize()==paNoError);

		/// make sure the default audio out is available.for the sake of simplicity we do not check for other outputs then oss on unix
		Q_ASSERT(Pa_GetDeviceInfo(  Pa_GetDefaultOutputDevice()));

		///open the default stream
		Q_ASSERT(Pa_OpenDefaultStream (
			&stream, 
			0,      ///no input channels
			2,      ///stereo output
			paFloat32,      ///32 bit floating output
			Pa_GetDeviceInfo( Pa_GetDefaultOutputDevice() )->defaultSampleRate,
			FRAMES_PER_BUFFER,
			PortaudioCallback,
			&avfile 
			)==paNoError);

		///start playback
		Q_ASSERT(Pa_StartStream( stream )==paNoError);
		}

	~AUDIOOUT()
		{
		///cleanup
    		Pa_StopStream( stream );
    		Pa_CloseStream( stream );
    		Pa_Terminate();
		}

	PaStream *stream;


};


static AUDIOOUT * audiout=NULL;





static QxtAudioPlayerStaticEofObjectHolder * eofo=NULL;




QxtAudioPlayer::QxtAudioPlayer(QObject * parent):QObject(parent){}


void QxtAudioPlayer::play(QString url)
	{
	if (!eofo)
		eofo=new QxtAudioPlayerStaticEofObjectHolder();


	if (!audiout)
		audiout = new AUDIOOUT();

	if (avfile)
		{
		///set null before delete to avoid crash of callback
		QxtAVFile * B=avfile;
		avfile=NULL;
		delete (B);
		}
	
	///intialise QxtAVFile. take care of the *2 QxtAVFile wants the amount of samples to push whereas portaudio means the amount per channel
	avfile = new QxtAVFile(url,FRAMES_PER_BUFFER*2);

	connect(avfile,SIGNAL(eof()),eofo,SLOT(f__eof()));


	///tell avfile to resample its output to the soundcards samplerate
	avfile->resample((int)Pa_GetDeviceInfo( Pa_GetDefaultOutputDevice() )->defaultSampleRate);



	}



void QxtAudioPlayerStaticEofObjectHolder::f__eof()
	{
    	Pa_StopStream(audiout->stream );
	QxtAVFile * B=avfile;
	avfile=NULL;
	if (B) delete (B);
	}


void QxtAudioPlayer::close()
	{
	if (audiout)	delete(audiout);
	if (avfile) 	delete(avfile);
	}



 QxtAudioPlayer::~QxtAudioPlayer()
	{
	if (eofo)	delete(eofo);
	if (audiout)	delete(audiout);
	if (avfile) 	delete(avfile);
	}
