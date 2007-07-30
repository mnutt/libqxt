#ifndef QxtStdin_H_GUARD
#define QxtStdin_H_GUARD
#include <qxtglobal.h>
#include <QIODevice>
#include "qxtfifo.h" 

class QSocketNotifier;
class QXT_CORE_EXPORT QxtStdin : public QxtFifo
	{
	Q_OBJECT
	public:
		QxtStdin(QObject * parent=0);
	private:
		QSocketNotifier * notify;
	private slots:	
		void activated(int );
	};
#endif
