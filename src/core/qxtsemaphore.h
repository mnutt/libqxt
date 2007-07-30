#ifndef QXTSEMAPHORE_H_NNN
#define QXTSEMAPHORE_H_NNN

#include <qxtpimpl.h>
#include <QString>
#include <qxtglobal.h>

class QxtSemaphorePrivate;
class QXT_CORE_EXPORT QxtSemaphore 
	{
	public:
		QxtSemaphore(QString );
		~QxtSemaphore();
		bool trylock();
		bool unlock();
	private:
    		QXT_DECLARE_PRIVATE(QxtSemaphore);
	};

#endif
