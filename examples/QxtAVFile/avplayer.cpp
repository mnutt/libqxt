/*!
portaudio + QxtAVFile example.
(c) 2007 Arvid Picciani (aep@exysREMOVETHIS.org) GPL

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

do not forget -lavcodec -lavformat -lportaudio (-lSoundTouch if you compiled QxtMedia with it)
*/
#include <portaudio.h>
#include <QCoreApplication>
#include <QxtAVFile>
#include <QxtSignalWaiter>

#define FRAMES_PER_BUFFER   1024

/*!
Portaudio will decide itself when to call this function. it expects to get 'frames' numbers of frames * channels  to be pushed to out. interleaved
This function allowes us to pass around a pointer to any object we like. we'll store our object pointer in it
*/
static int PortaudioCallback(const void *, void *outputBuffer,unsigned long ,const PaStreamCallbackTimeInfo* ,PaStreamCallbackFlags ,void *userData )
    {
    ///prepare the buffer
    float *out = (float*)outputBuffer;
    ///get the user data
    QxtAVFile*avfile = (QxtAVFile*)userData;

    ///flip the data to portaudios callback buffer
    avfile->flip(out);

    return paContinue;
    }



int main(int argc, char **argv)
    {
    ///we all know what it does ;)
    QCoreApplication app (argc,argv);

    ///pa state structs
    PaStream *stream;

    ///init portaudio
    Q_ASSERT(Pa_Initialize()==paNoError);

    /// make sure the default audio out is available.for the sake of simplicity we do not check for other outputs then oss on unix
    Q_ASSERT(Pa_GetDeviceInfo(  Pa_GetDefaultOutputDevice()));

    ///intialise QxtAVFile. take care of the *2 QxtAVFile wants the amount of samples to push whereas portaudio means the amount per channel
    QxtAVFile avfile(argv[1],FRAMES_PER_BUFFER*2);

    ///tell avfile to resample its output to the soundcards samplerate
    avfile.resample((int)Pa_GetDeviceInfo( Pa_GetDefaultOutputDevice() )->defaultSampleRate);
    
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

    ///wait for eof.
    QxtSignalWaiter waiter(&avfile, SIGNAL(eof()));
    waiter.wait();

    ///cleanup
    Pa_StopStream( stream );
    Pa_CloseStream( stream );
    Pa_Terminate();

    return 0;
    }
