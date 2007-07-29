#include <qxtpimpl.h>
#include <QString>

class QxtSemaphorePrivate;
class QxtSemaphore 
	{
	public:
		QxtSemaphore(QString );
		~QxtSemaphore();
		bool trylock();
		bool unlock();
	private:
    		QXT_DECLARE_PRIVATE(QxtSemaphore);
	};
