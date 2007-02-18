/**

\class QxtRingBuffer QxtRingBuffer

\ingroup media

\brief thread safe ring buffer
 
 * The key attribute of a ringbuffer is that it can be safely accessed
 * by two threads simultaneously -- one reading from the buffer and
 * the other writing to it -- without using any synchronization or
 * mutual exclusion primitives.  For this to work correctly, there can
 * only be a single reader and a single writer thread.  Their
 * identities cannot be interchanged.
*/


#include "QxtRingBuffer.h"
#include "ringbuffer.h"

class QxtRingBufferPrivate : public QxtPrivate<QxtRingBuffer>
	{
	QXT_DECLARE_PUBLIC(QxtRingBuffer);	
	public:
		void construct(unsigned long size)
			{
			ring= jack_ringbuffer_create(size);
			}
	
		 void destruct()
			{
			jack_ringbuffer_free(ring);
			}

		unsigned long read(char * destination, unsigned long size)
			{
			return jack_ringbuffer_read(ring , destination,size);
			}
		
		unsigned long available()
			{
			return jack_ringbuffer_read_space(ring);
			}

		unsigned long write(char * source, unsigned long size)
			{
			return jack_ringbuffer_write(ring, source,size);
			}

	private:
		jack_ringbuffer_t *  ring;
	};



//-----------------------------interface-------------------------------


QxtRingBuffer::QxtRingBuffer	(unsigned long size, QObject * parent):QObject(parent)
	{
	qxt_d().construct(size);
	}

 QxtRingBuffer::~QxtRingBuffer	()
	{
	qxt_d().destruct();
	}

unsigned long QxtRingBuffer::read	(char * destination, unsigned long size)
	{
	return qxt_d().read(destination,size);
	}
unsigned long QxtRingBuffer::available	()
	{
	return qxt_d().available();
	}
unsigned long QxtRingBuffer::write	(char * source, unsigned long size)
	{
	return qxt_d().write(source,size);
	}




