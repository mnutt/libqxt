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

		unsigned long peek(char * destination, unsigned long size)
			{
			return jack_ringbuffer_peek (ring,destination, size);
			}
		void get_read_vector    (char  **buffer,unsigned long * length)
			{
			jack_ringbuffer_data_t  vec[2];
			jack_ringbuffer_get_read_vector(ring,vec);
			*buffer=vec[0].buf;
			*length=vec[0].len;
			}
		void get_write_vector   (char  **buffer,unsigned long * length)
			{
			jack_ringbuffer_data_t  vec[2];
			jack_ringbuffer_get_write_vector(ring,vec);
			*buffer=vec[0].buf;
			*length=vec[0].len;
			}
		void read_advance       (unsigned long length)
			{
			jack_ringbuffer_read_advance(ring, length);
			}
		void write_advance       (unsigned long length)
			{
			jack_ringbuffer_write_advance(ring, length);
			}

	private:
		jack_ringbuffer_t *  ring;
	};



//-----------------------------interface-------------------------------

/**
default constructor. takes the ring \p size as argument
*/	
QxtRingBuffer::QxtRingBuffer	(unsigned long size, QObject * parent):QObject(parent)
	{
	qxt_d().construct(size);
	}
/**
destructor
*/	
QxtRingBuffer::~QxtRingBuffer	()
	{
	qxt_d().destruct();
	}
/**
read \p size bytes to \p destination
*/	
unsigned long QxtRingBuffer::read	(char * destination, unsigned long size)
	{
	return qxt_d().read(destination,size);
	}
/**read but do not delete the data from the buffer*/
unsigned long QxtRingBuffer::peek	(char * destination, unsigned long size)
	{
	return qxt_d().peek(destination,size);
	}
/**
check how much data is there available for read
*/	
unsigned long QxtRingBuffer::available	()
	{
	return qxt_d().available();
	}
/**
write \p size bytes from \p destination to the ring
*/	
unsigned long QxtRingBuffer::write	(char * source, unsigned long size)
	{
	return qxt_d().write(source,size);
	}
/**
get a direct pointer to data. \n

Use this to get direct READ access. do not write! \n
don't forget to call read_advance after reading from this pointer.\n
\p length  is the amount of bytes that can be read straight. \n
even if available says there is more data, you may not read more then \p length  directly. 
(the data is not continues in memory!)
*/	
void QxtRingBuffer::get_read_vector    (char  **buffer,unsigned long * length)
	{
	qxt_d().get_read_vector(buffer,length);
	}
/**
get a direct pointer to data. \n

Use this to get direct WRITE access. do not read! \n
don't forget to call write_advance after writing  to this pointer.\n
\p length  is the amount of bytes that can be written straight. \n
you may not write more then \p length  directly.
(the data is not continues in memory!)
*/	
void QxtRingBuffer::get_write_vector   (char  **buffer,unsigned long * length)
	{
	qxt_d().get_write_vector(buffer,length);
	}
/**
call this to indicate how much you have read from the pointer you got from get_read_vector
*/
void QxtRingBuffer::read_advance       (unsigned long length)
	{
	qxt_d().read_advance (length);
	}
/**
call this to indicate how much you have written from the pointer you got from get_write_vector
*/
void QxtRingBuffer::write_advance       (unsigned long length)
	{
	qxt_d().write_advance (length);
	}



