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




static	PaStream *stream;


QxtAudioPlayer::QxtAudioPlayer(QObject * parent):QObject(parent)
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

 QxtAudioPlayer::~QxtAudioPlayer()
	{

	}




void QxtAudioPlayer::play(QxtAVFile * file)
	{
	if(avfile)avfile->reset();
	avfile=NULL;

	connect(file,SIGNAL(eof()),this,SLOT(feof()));

	///tell avfile to resample its output to the soundcards samplerate
	file->resample((int)Pa_GetDeviceInfo( Pa_GetDefaultOutputDevice() )->defaultSampleRate);

	avfile=file;
	}



void QxtAudioPlayer::feof()
	{
// 	if(!(QxtAVFile* )sender())return;
// 	if(avfile)avfile->reset();
	avfile=NULL;

	}



