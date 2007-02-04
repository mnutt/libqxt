#include <QObject>
#include <QByteArray>
#include <Qxt/qxtglobal.h>


/**
\class QxtMetaBall QxtMetaBall
\ingroup kit

\brief signal/slot connections with expressions

sometimes you want to just connect a signal with no parameter to a slot with, and give the parameter.
QxtMetaBall allowes you even to put expressions in. It requires the Qxt Meta Object Extender.
if you use qmake, just add CONFIG+=mox to your project file, it should automaticly invoce mox to create the nesacary mox_*  files, do NOT include those auto generated files yourself.

Usage examples:
\code
QxtMetaBall::connect(sender,SIGNAL(signal(int)),receiver,SLOT(slot(bool)),BALL(value>0));
QxtMetaBall::connect(write, SIGNAL(clicked()), text, SLOT(write(QString)),BALL(QString("foobar")));
QxtMetaBall::connect(write, SIGNAL(clicked()), text, SLOT(write(QString)),BALL(textBox->text()));

\endcode

*/

///TODO:include classname in the signature to avoid colision


#define BALL(x) (QByteArray("Ball_")+(QByteArray(QByteArray(__FILE__)+QByteArray::number(__LINE__)).toBase64 ().replace("=","")))

class QXT_KIT_EXPORT QxtMetaBall
	{
	public:

	static bool connect(QObject *sender,char *signal,QObject* receiver,char *slot,QByteArray ball);
	static bool disconnect(QObject *sender,char *signal,QObject* receiver,char *slot,QByteArray ball);
	private:

	static QObject * MetaTable()
		#ifdef BUILDING_QXT_LIBRARY
			{qWarning("QxtMetaBall should not be called from here! That is either a bug or you defined BUILDING_QXT_LIBRARY acidently."); return 0;}
		#else
			;
		#endif
	};

