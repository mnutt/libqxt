#include <QObject>
#ifndef INT64_C
        #define INT64_C Q_INT64_C
#endif
#include <ffmpeg/avcodec.h>
#include <ffmpeg/avformat.h>


int main (int,char**)
	{
        av_register_all();
        avcodec_init();
        avcodec_register_all();
	return 0;
	}


