#include "QxtAVFile.h"
#include "QxtRingBuffer.h"
#ifndef INT64_C 
	#define INT64_C Q_INT64_C
#endif
#include <ffmpeg/avcodec.h>
#include <ffmpeg/avformat.h>

#ifdef HAVE_SPEEX
#include "resample/speex_resampler.h"
#endif
#include <QMutex>

class QxtAVFilePrivate : public QObject, public QxtPrivate<QxtAVFile>
	{
	Q_OBJECT

	public:

	void destroy();

	///callbacks


	QxtError open(QString url);


	QxtError read(short*, unsigned long length);
	QxtError read(float*, unsigned long length);
	QxtError read(char *, unsigned long length);

	QxtError seek(double time);
	double 	time()   const;
	double 	length() const;

	QxtError seekP(char time);
	char 	timeP()   const;

	bool isEof();
	bool eof;

	



	///internals
	QxtError getFrame();




	///the ring
	QxtRingBuffer * ring;

	///ffmpeg 
	AVCodec 		*	codec;
	AVCodecContext		*	codec_context;
	AVFormatContext 	*	format_context;
	AVPacket 			packet;


	int AudioStreamIndex;

	///the HugeBuffer
	char *hugeBuffer;
	unsigned long hugeSize;
	void checkHugeBounds();

	///state
	bool opened;




	///system mutex. lock this when doing stuff that could be thread unsafe
	QMutex mutex;


	///resampler
	unsigned long samplerate() const;
	QxtError setSamplerate(const unsigned long);
	unsigned long samplerate_p;

#ifdef HAVE_SPEEX
	SpeexResamplerState * resampler;
#endif

	};
