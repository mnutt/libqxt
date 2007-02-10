/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QxtAVFileH
#define QxtAVFileH

#include <QThread>
#include <QString>
#include <QStringList>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

/**

\class QxtAVFile QxtAVFile

\ingroup media

\brief AV decoder
 

A very easy to use interface for libavcodec and libavformat.

The data is processed in the background, you will not notice it as the flip function returns imidiatly.
the flip functionality is especialy designed for use in real time av processing. Currently the class can only provide you Audio.

pass the filename to open and the fliplen to the ctor.
then every time you call flip() on a buffer, it will push the amount of samples defined by fliplen to the passed buffer.

the buffer is interleaved (alternating right/left) and always stereo.
the fliplean is NOT meant as per channel. it is the amount of data for all channels

\bug currently fliplen must be minimal 1024*2 in order to get the decoder working.

*/


class QxtAudioPlayer;
class QXT_MEDIA_EXPORT QxtAVFile :  public QThread
	{
	Q_OBJECT
	public:

		/**default constructor. 
		pass filename and fliplen.
		*/
		
 		QxtAVFile(QString filename,int fliplen,int flags=0,QObject *parent=0);
		/**default constructor. 
		if you just use QxtAVFile for playback with QxtAudioPlayer, use this ctor to use the default fliplen
		\bug does not work, for some odd reason... not debugable
		*/
		QxtAVFile(QString filename,QxtAudioPlayer*, int flags=0,QObject *parent=0);

		~QxtAVFile();








		/** 
		fill the buffer passed with data.
		returns <0 in case of an error or eof.
		*/
		int flip(float*);

		int flip(short*);

		/**
		Set it to indicate you want the output to be resampled to a specific samplerate.
		This adds aditional noice but is not very cpu intensive.
		Setting it to the current files samplerate or to 0 will switch  the resampler off.
		Resetting it in the middle of the decoding process will sound awful and may corupt memory.
		\note If you excluded SoundTouch from the build process this will return imidiatly -111, doing nothing.
		*/
		int resample(unsigned int samplerate);




		/**
		returns the ID3 tag
		or an empty list if there is no supported tag.

		the order is: 
		title,author,album,copyright,comment,year,track,genre
		*/
		QStringList ID3();




		///seek to the specified playback time in seconds.
		void seek(double time);

		///returns the current playback time in seconds.
		double time();

		///playback length of the file in seconds.
		double length();

		///reset
		void reset();



		bool opened(){return opened_m;}


	signals:
		/**
		End of File Signal.
		*/
		void eof();


		void error(QString);

		///\internal

	private:	



		///index of the audio stream
		int	AudioStreamIndex;
		///index of the video stream
		int	VideoStreamIndex;

		///lock the decoder thread
		float *	decoderlock_b;

		///file->decoder->buffer
		int	getFrame(float * out);
		///decoder->(resample)->buffer
		void	refill(float* WRITE);
		///decoder thread
		void	run();
		
		///resampling ratio
		double  AORatio;
		///decoder -> resampler buffer
		float *	DSRC;
		long	DSRC_LEN;
		///the flipbuffer (we use doublebuffering to get realtime capability)
		float *	OUT1;
		float *	OUT2;
		///indicates the next write buffer
		bool	WF;
		///indicates the current write buffer
		bool	HF;
		///the fliplen
		unsigned long	fliplen_m;
		///resample indicator
		unsigned int 	resample_m;

		///the length of the minimal  buffer to fill fliplen_m
		unsigned long	fliplen_unsized;

		///playbacktime
		double playbacktime;

		///indicate that the next buffer is the last
		bool eof_f;///flip


		int flags_d;

		///canot call flip
		bool blocked;


		bool opened_m;

	};



#endif

