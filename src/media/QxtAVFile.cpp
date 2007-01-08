#include "QxtAVFile.h"

#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

#include <limits> 
#include <cassert>
#include <cmath>
#include <iostream>


#include <ffmpeg/avcodec.h>
#include <ffmpeg/avformat.h>

#define QxtMediaLibsSoundTouch
#define MINIMAL_SRC_LEN 5000

#ifdef QxtMediaLibsSoundTouch
#include <soundtouch/SoundTouch.h>
#endif

///assert
#define AV_ASSERT(cmd) if(cmd < 0) {qDebug()<<"QxtAVFile aborted at line "<<__LINE__; return;}

///this scales the 16bit output to some usable 32bit float. actualy this will not increase quality but usability
#define scale(shortval) (float)shortval / (float)std::numeric_limits<short>::max()

#define printFArray(array,size) std::cout<<"::"<<size<<"::[";  for (int i=0;i<size;i++) std::cout<<array[i]<<"|"; std::cout<<"]::"<<std::endl;


///the ffmpeg statestructs
static AVCodec 		*	codec;
static AVCodecContext	*	codec_context;
static AVFormatContext 	*	format_context;


#ifdef QxtMediaLibsSoundTouch
static soundtouch::SoundTouch resampler;
#endif

//-------------------------------------------------------------



QxtAVFile::QxtAVFile(QString filename,int fliplen,QObject *parent):QThread(parent)
	{
	///defaults
	AORatio=1.0;
	DSRC_LEN=0;
	WF=false;
	HF=true;
	fliplen_m=0;
	resample_m=0;
	playbacktime=0.0;

	/// \bug buffsize must be at least 2048
 	assert(fliplen>=2048);
	assert(!filename.isEmpty());

	//!init
	av_register_all();
	avcodec_init();
	avcodec_register_all();
	
	//!open the file and get some information out of it
	AV_ASSERT(av_open_input_file(&format_context,filename.toLocal8Bit(), NULL, 0, NULL));
	AV_ASSERT(av_find_stream_info(format_context));
	assert(format_context);
	
	//!find the first audio stream. Just iterate over all found streams and take the first audio stream. good enough for this example
	AudioStreamIndex=-1;
	for(int i=0; i<format_context->nb_streams; i++)
		if(format_context->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO)
			{AudioStreamIndex=i;break;}
	AV_ASSERT(AudioStreamIndex);

	//!get the codec context for the  stream
	codec_context=format_context->streams[AudioStreamIndex]->codec;

	//!find the decoder
	codec=avcodec_find_decoder(codec_context->codec_id);
	assert(codec);

	//!open the codec 
	AV_ASSERT(avcodec_open(codec_context, codec));


	///prepare the buffers
	fliplen_m=fliplen;
	OUT1= new float[fliplen_m+MINIMAL_SRC_LEN];
	OUT2= new float[fliplen_m+MINIMAL_SRC_LEN];

	for (unsigned int i=0;i<fliplen_m;i++)
		{
		OUT1[i]=0;
		OUT2[i]=0;

		}
	DSRC=new float[fliplen_m*8];


	///prepare the decoder
	decoderlock_b=NULL;
 	start();

	}

//-------------------------------------------------------------

QxtAVFile::~QxtAVFile()
	{

	//!clean up ffmpeg
	avcodec_close(codec_context);
	av_close_input_file(format_context);
	}



//-------------------------------------------------------------
int QxtAVFile::resample(unsigned int samplerate)
	{

	#ifdef QxtMediaLibsSoundTouch

	if (samplerate==0 || samplerate == (unsigned)codec_context->sample_rate)
		{
		resample_m=0;
		return 0;
		}

	resample_m=samplerate;


	AORatio= (double)codec_context->sample_rate/(double)samplerate;
	fliplen_unsized = (long)round((double)fliplen_m*AORatio)+1;


	//!prepare the sample converter
	resampler.setSampleRate(codec_context->sample_rate);
	resampler.setChannels(2);
	resampler.setRate(AORatio);
	#endif

	return 1;
	}




//-------------------------------------------------------------



double QxtAVFile::time()
	{
	return playbacktime;
	}

//-------------------------------------------------------------


void QxtAVFile::seek(double time)
	{
	if(format_context->duration<0){qWarning("playing a stream, won't seek.");return;}
	AV_ASSERT(av_seek_frame   (format_context, -1,(long)(AV_TIME_BASE*time), 0 ));
	playbacktime=time;
	}



//-------------------------------------------------------------
double QxtAVFile::length()
	{
	return ((double)format_context->duration/(double)AV_TIME_BASE)/**AORatio*/;
	}

//-------------------------------------------------------------
int QxtAVFile::flip(float* out)
	{
	///if we have an xrun try to wait for the buffer
	while (HF==WF && decoderlock_b != NULL){usleep(10);qWarning("warning: underrun detected, waiting 10 usecs.");}

	if(WF)
		{
		decoderlock_b=OUT2;
		memcpy(out,OUT1,fliplen_m*sizeof(float));
		WF=false;
		}
	else
		{
		decoderlock_b=OUT1;
		memcpy(out,OUT2,fliplen_m*sizeof(float));
		WF=true;
		}


	if (resample_m)

		{playbacktime+=((double)fliplen_m/2.0)/(double)resample_m;}
	else
		{playbacktime+=((double)fliplen_m/2.0)/(double)codec_context->sample_rate;}

	return fliplen_m;
	}


//-------------------------------------------------------------

/**
gets a frame from libavformat and iterates over its contents to 
decode every frame in it. then it scales the frame and pushs it to the passed buffer
*/
int QxtAVFile::getFrame(float * out)
	{
	assert(out==DSRC );

	short outbuf[AVCODEC_MAX_AUDIO_FRAME_SIZE];
	unsigned char *inbuf;
	int outbufsize, size,inlen,olen;
	olen=0;
	AVPacket pkt;



	forever
	{
	/// read a packet 
	if (av_read_frame(format_context, &pkt)<0){emit(eof());return -1;}

	//!skip packages that don't belong to the wanted stream
	if (pkt.stream_index==AudioStreamIndex)break;
	}


	size = pkt.size;
	inbuf = pkt.data;
	while (size > 0) 
		{
		inlen = avcodec_decode_audio(codec_context,(short*)outbuf, &outbufsize, inbuf, size);
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

		int outbuflen=outbufsize/sizeof(short);

		for (int i = 0;i<outbuflen;i++)
			{
			*out++= scale(outbuf[i]);
			///doublicate the sample if the source was mono
			if (codec_context->channels==1)
				*out++=scale(outbuf[i]);
			}

		olen+=outbuflen;
		if (codec_context->channels==1)olen+=outbuflen;
		}

	if (pkt.data) 
		av_free_packet (&pkt);
	return olen;
	}

//-------------------------------------------------------------



void QxtAVFile::run()
	{
	forever
		{
		if (decoderlock_b==NULL)
			{msleep(10);continue;}
		HF=(decoderlock_b==OUT2);
		refill(decoderlock_b);
		decoderlock_b=NULL;
		}
	}



//-------------------------------------------------------------



/**
fill the outputbuffer with the requested amount of data
resample if desired
*/
void QxtAVFile::refill(float * WRITE)
	{

	#ifdef QxtMediaLibsSoundTouch
	if (resample_m)
		{
		while(resampler.numSamples()<fliplen_m+1)
			{
			DSRC_LEN=getFrame(DSRC);
			resampler.putSamples(DSRC,DSRC_LEN/2);
	
			}
		assert(resampler.receiveSamples(WRITE,fliplen_m/2)==fliplen_m/2);	
		return;
	
		}
	else
		{
	#endif

		static float * DSRCP=DSRC;
		int write=fliplen_m;
		float * out=WRITE;
	
		///while there are not enough samples written
		while(write>0)
			{
			///if the decoder buffer is empty get data
			if(!DSRC_LEN)
				{
				DSRCP = DSRC;
				DSRC_LEN=getFrame(DSRC);
				}
	
			///beg it doesn't exploede
			assert((unsigned)DSRC_LEN<=fliplen_m*4);
	
			///get as much data as avilable but not more then requested
			int l= qMin(DSRC_LEN,(long)write);
			///push
			memcpy(out,DSRCP,l*sizeof(float));
			///forward iterators
			write-=l;
			out+=l;
			DSRCP+=l;
			DSRC_LEN-=l;
	
			}
	#ifdef QxtMediaLibsSoundTouch
		}
	#endif





	}











