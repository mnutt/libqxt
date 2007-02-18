#include "QxtAVFile_p.h"

#include <cassert>
#include <limits> 

#include <QxtCore/QxtHyperMacros>


QxtError QxtAVFilePrivate::open(QString filename)
	{
	///av init
	av_register_all();
	avcodec_init();
	avcodec_register_all();
	
	///open the file
	if (av_open_input_file(&format_context,filename.toLocal8Bit(), NULL, 0, NULL) < 0) QXT_DROP(Qxt::FileIOError);

	assert(format_context);

	if (av_find_stream_info(format_context)<0) QXT_DROP( Qxt::FormatError);
	
	//!find the first audio stream. 
	AudioStreamIndex=-1;
	for(int i=0; i<format_context->nb_streams; i++)
		if(format_context->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO)
			{AudioStreamIndex=i;break;}
	if(AudioStreamIndex<0)QXT_DROP( Qxt::FormatError);

	//!get the codec context for the  stream
	codec_context=format_context->streams[AudioStreamIndex]->codec;

	//!find the decoder
	codec=avcodec_find_decoder(codec_context->codec_id);
	if (!codec)QXT_DROP( Qxt::CodecError);

	//!open the codec 
	if (avcodec_open(codec_context, codec)<0)QXT_DROP( Qxt::CodecError);

	//!prepare the ring
	ring= new QxtRingBuffer(codec_context->sample_rate*4,this);

	//!prepare the huge buffer
	hugeSize=codec_context->sample_rate*4;
	hugeBuffer= new char [hugeSize];
	hugeBuffer[hugeSize-1]='k';

	///set opened
	opened=true;

	QXT_DROP_OK
	}

//-------------------------------------------------------------

void QxtAVFilePrivate::destroy()
	{
	if (!opened)return;
	if(codec_context)avcodec_close(codec_context);
	if(format_context)av_close_input_file(format_context);
	if(ring)delete ring;
	}


//-------------------------------------------------------------
///overrun protection
void QxtAVFilePrivate::checkHugeBounds()
	{
	assert(hugeBuffer[hugeSize-1]=='k');
	}

//-------------------------------------------------------------

QxtError QxtAVFilePrivate::seek(double time)
	{
	if (!opened)			QXT_DROP(Qxt::NotInitialised);
	if (!format_context)		QXT_DROP(Qxt::Bug);

	if (format_context->duration<0)	QXT_DROP(Qxt::LogicalError);

	if (av_seek_frame   (format_context, -1,(long)(AV_TIME_BASE*time), 0 )<0) QXT_DROP(Qxt::FormatError);

	QXT_DROP_OK
	}

//-------------------------------------------------------------


double QxtAVFilePrivate::length() const
	{
	if (!opened)		return 0.0;
 	if (!format_context)	return 0.0;

	return ((double)format_context->timestamp/(double)AV_TIME_BASE);
	}


//-------------------------------------------------------------

double QxtAVFilePrivate::time() const
	{
	if (!opened)		return 0.0;
 	if (!format_context)	return 0.0;

	return ((double)format_context->timestamp/(double)AV_TIME_BASE);
	}

//----------------------------------------------


QxtError  QxtAVFilePrivate::seekP(char time)
	{
	return seek (((double)time/100.0)*length());
	}

//----------------------------------------------

char 	 QxtAVFilePrivate::timeP()   const
	{
	return (char)((time()/length())*100.0);
	}



//----------------------------------------------
bool  QxtAVFilePrivate::isEof()
	{

	return false; ///TODO: make this usefull
	};


//----------------------------------------------

unsigned long QxtAVFilePrivate::samplerate()
	{
	if (!opened)		return 0;
	if (!codec_context)	return 0;
	return codec_context->sample_rate;
	}



//----------------------------------------------

QxtError QxtAVFilePrivate::read(short* target, unsigned long length)
	{
	if (!opened)			QXT_DROP(Qxt::NotInitialised);
	if (isEof())			QXT_DROP(Qxt::EndOfFile);

	
	while (ring->available() < length*sizeof(short))
		getFrame();				///TODO: make it realtime and error safe



	if (ring->read((char*)target,length*sizeof(short))!=length*sizeof(short))QXT_DROP(Qxt::Bug);
	QXT_DROP_OK
	}
//----------------------------------------------

QxtError QxtAVFilePrivate::read(float* target, unsigned long length)
	{
	short aa[length];
	short * ab= aa;

	QXT_DROP_F(read(aa,length));

	fortimes(length)
		*target++=(float)*ab++ / (float)std::numeric_limits<short>::max();


	QXT_DROP_OK
	};
//----------------------------------------------

QxtError QxtAVFilePrivate::read(char * target, unsigned long length)
	{
	fortimes(length)*target++=0;		///TODO:make this usefull
	QXT_DROP(Qxt::NotImplemented);
	};


//----------------------------------------------

/**
gets a frame from libavformat and iterates over its contents to 
decode every frame in it. then it scales the frame and pushs it to the passed buffer
*/
QxtError QxtAVFilePrivate::getFrame()
	{
	assert(&packet);


	do
		{
		if (av_read_frame(format_context, &packet)<0)QXT_DROP(Qxt::EndOfFile);
		}
	while (packet.stream_index!=AudioStreamIndex);



	int size = packet.size;
	uint8_t * inbuf = packet.data;

	while (size > 0) 
		{
		int outbufsize,inlen;
		inlen = avcodec_decode_audio(codec_context,(short *)hugeBuffer, &outbufsize, inbuf, size);
		checkHugeBounds();
		codec_context->frame_number++;
		

               	/// on any  error, we skip the frame
		if (inlen < 0)
			{
			size = 0;
			break;
			}

		///"remove" the decoded sample from the read frame
		inbuf += inlen;
		size -= inlen;

		///if the sample is empty we don't want it
		if (outbufsize <= 0)
			continue;


		if (codec_context->channels==1)
			{
			///doublicate the sample if the source was mono
			for (int i = 0;i<outbufsize;i+=sizeof(short))
				{
				ring->write(&hugeBuffer[i],sizeof(short));
				ring->write(&hugeBuffer[i],sizeof(short));
				}
			}
		else
			{
			ring->write(hugeBuffer,outbufsize);
			}
		}

 	if (packet.data) 
 		av_free_packet (&packet);	///TODO: erm, is this good?
	QXT_DROP_OK
	}





