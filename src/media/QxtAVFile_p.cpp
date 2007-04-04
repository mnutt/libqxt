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
#include "QxtAVFile_p.h"

#include <cassert>
#include <limits> 

#include <QxtCore/QxtHyperMacros>

QxtError QxtAVFilePrivate::open(QString filename)
	{
	///defaults
	eof=false;
	samplerate_p=0;

	#ifdef HAVE_SPEEX
	resampler=NULL;
	#endif

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
	for(unsigned int i=0; i<format_context->nb_streams; i++)
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

	//!prepare the huge buffer
	hugeSize=codec_context->sample_rate+AVCODEC_MAX_AUDIO_FRAME_SIZE;
	hugeBuffer= new char [hugeSize];
	hugeBuffer[hugeSize-1]='k';

	//!prepare the ring
	ring= new QxtRingBuffer(hugeSize,this);

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
	#ifdef HAVE_SPEEX
	if(resampler)speex_resampler_destroy(resampler);
	#endif
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


	/*speex_resampler_reset_mem(resampler);*/

	QXT_DROP_OK
	}

//-------------------------------------------------------------


double QxtAVFilePrivate::length() const
	{
	if (!opened)		return 0.0;
 	if (!format_context)	return 0.0;
	return ((double)format_context->duration/(double)AV_TIME_BASE);
	}


//-------------------------------------------------------------

double QxtAVFilePrivate::time() const
	{
	if (!opened)		return 0.0;
 	if (!format_context)	return 0.0;
	if (!format_context->cur_st) return 0.0;




	return ((double)format_context->cur_st->cur_dts/(double)format_context->cur_st->time_base.den);
	}

//----------------------------------------------


QxtError  QxtAVFilePrivate::seekP(char time)
	{
	return seek (((double)time/100.0)*length());
	}

//----------------------------------------------

char 	 QxtAVFilePrivate::timeP()   const
	{
	if (!length())return 0;
	return (char)((time()/length())*100.0);
	}



//----------------------------------------------
bool  QxtAVFilePrivate::isEof()
	{
	return (eof && (ring->available() < 2*sizeof(short)));
	};




//----------------------------------------------

QxtError QxtAVFilePrivate::read(short* target, unsigned long length)
	{
	if (!opened)			QXT_DROP(Qxt::NotInitialised);
	if (isEof())			QXT_DROP(Qxt::EndOfFile);
	if (length >hugeSize)		QXT_DROP(Qxt::LogicalError);
	
	mutex.lock();


	int write=length;
	while(write>0)
		{

		#ifdef HAVE_SPEEX
		if (samplerate_p!=0 && resampler!=NULL)
			{

			
	
			long unsigned int in_size;
			char *  in;
			ring->get_read_vector(&in,&in_size);

			
			int in_len = (in_size/sizeof(short))/2;
			
			int written=write/2;
			speex_resampler_process_interleaved_int(resampler, (short*)in, &in_len, target, &written);
	
		
			ring->read_advance((in_len*sizeof(short))*2);
			write-=written*2;
			target+=written*2;

			}
		else
			{
		#endif		
			int e=ring->read((char*)target,write*sizeof(short))/sizeof(short);
			write-=e;
			target+=e;
		#ifdef HAVE_SPEEX
			}
		#endif


 		if (!write)continue;  //this is a dirty hack :( to get the resampled stream in sync (avoid overread on a realtime stream)
		///TODO: make it realtime 
		QxtError e= getFrame();
		
		if(e==Qxt::EndOfFile)
			{
			eof=true;
			mutex.unlock();
			QXT_DROP(Qxt::EndOfFile);
			}
		
		QXT_DROP_F(e);
		
		}


	mutex.unlock();
	QXT_DROP_OK
	}
//----------------------------------------------

QxtError QxtAVFilePrivate::read(float* target, unsigned long length)
	{
	short aa[length];


	short * ab= aa;
	
	
	QXT_DROP_F(read(aa,length));

	fortimes(length)
		{
		*target=(float)*ab++ / (float)std::numeric_limits<short>::max();
		if (*target>1.0)*target=1.0;
		if (*target<-1.0)*target=-1.0;
		
		target++;
		
		}


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
		outbufsize=hugeSize;
		inlen = avcodec_decode_audio2(codec_context,(short *)hugeBuffer,&outbufsize, inbuf,size);





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





//----------------------------------------------

unsigned long QxtAVFilePrivate::samplerate() const
	{
	if (!opened)		return 0;
	if (!codec_context)	return 0;
	if (samplerate_p==0)return codec_context->sample_rate;
	return samplerate_p;
	}


//----------------------------------------------

QxtError QxtAVFilePrivate::setSamplerate(const unsigned  long a) 
	{
	#ifdef HAVE_SPEEX

	mutex.lock();
	samplerate_p=a;

	if(resampler==NULL)
		{
		resampler = speex_resampler_init(2, codec_context->sample_rate, samplerate_p,5);
		if (resampler==NULL)QXT_DROP(Qxt::InsufficientMemory);	
		}
	else
		{
		speex_resampler_set_rate(resampler,codec_context->sample_rate, samplerate_p);
		}	


	mutex.unlock();
	QXT_DROP_OK
	#else
	QXT_DROP(Qxt::NotImplemented)
	#endif
	}






