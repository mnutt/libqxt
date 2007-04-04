/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/
#include <SDL/SDL.h>
#include <QCoreApplication>
#include <QxtAVFile>
#include <QxtSignalWaiter>
#include <QDebug>

#define FRAMES_PER_BUFFER   1024

#include <limits> 
static QxtAVFile *avfile;

/**
The SDl Audio Callback
*/
static void Callback (void *, Uint8 *stream, int size)
	{
	short *out = (short*)stream;

	int fliplen = size/sizeof(short);


	///we could use the flip(short*) function of QxtAVFile, but since we need to process the samples anyway, we avoid overhead
	float a[fliplen];
	Q_ASSERT_X(avfile->flip(a)==fliplen,"Callback","unexpected buffersize");
	for (int i=0;i<fliplen;i++)
		{
		Q_ASSERT_X(a[1]<=1.1  &&  a[1]>=-1.1,"Callback","unhandled clipping");
		*out++=(short)(a[i]*0.99*std::numeric_limits<short>::max());
		}
	}


int main(int argc, char **argv)
	{
	///we all know what it does ;)
	QCoreApplication app (argc,argv);

	///init sdl
	Q_ASSERT(SDL_Init (SDL_INIT_AUDIO)>=0);


	///sdl lets us pass a wanted spec, and it tryes to respect that. if we let it , it will try to find a mode less you intensive though
	SDL_AudioSpec wanted_spec,got_spec;

	wanted_spec.freq=48000;
	wanted_spec.format=AUDIO_S16SYS;
	wanted_spec.channels=2;
        wanted_spec.silence = 0;

	wanted_spec.samples=1024;
	wanted_spec.callback=Callback;
	wanted_spec.userdata=NULL;
	got_spec=wanted_spec;


	///set the second parameter to NULL, to enforce the spec above, if you encounter problems
	Q_ASSERT_X(SDL_OpenAudio (&wanted_spec, &got_spec)>=0,"SDL",SDL_GetError());


	///intialise QxtAVFile. take care of the *2 QxtAVFile wants the amount of samples to push whereas sdl means the amount per channel
	avfile= new QxtAVFile(argv[1],got_spec.samples*2);

	///tell avfile to resample its output to the soundcards samplerate
  	avfile->resample(got_spec.freq);
 
	///unpause
	SDL_PauseAudio (0);

	///wait for eof.
	QxtSignalWaiter waiter(avfile, SIGNAL(eof()));
	waiter.wait();

	///cleanup
	SDL_CloseAudio();
	return 0;
	}
