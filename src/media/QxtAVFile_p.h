#include "QxtAVFile.h"
#include "QxtRingBuffer.h"

#include <ffmpeg/avcodec.h>
#include <ffmpeg/avformat.h>


class QxtAVFilePrivate : public QObject,QxtPrivate<QxtAVFile>
	{
	Q_OBJECT
	QXT_DECLARE_PUBLIC(QxtAVFile);	
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


	unsigned long samplerate();
	



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




	};
