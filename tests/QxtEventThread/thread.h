#include <QObject>
#include <QDebug>
#include <QThread>
class thread : public QObject
	{
	Q_OBJECT

	public slots:

		void call()
			{
			qDebug()<<"slot in Thread "<<QThread::currentThreadId ();
			}


	};
