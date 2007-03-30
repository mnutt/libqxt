#include "QxtWebSession.h"

#include <QThread>
#include "QxtWebApplication_p.h"

/*!
	\class QxtWebSession QxtWebSession
	\ingroup web
	\brief an interface to the clients session worker

*/



/*!
\fn  
destroy a session thread after the current request has been handled.
*/
void QxtWebSession::destroy()
	{
	QxtWebApplicationThread * o= qobject_cast<QxtWebApplicationThread *>(QThread::currentThread ());

	if (!o)
		{
		qWarning("QxtWebSession::destroy() can only be called from inside a worker thread. e.g. from a controller.");
		return;
		}
	o->quit();
	}

