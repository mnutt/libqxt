#include <QObject>
#include <QByteArray>


/**
\class QxtMetaBall QxtMetaBall

signal/slot connections with expressions

sometimes you want to just connect a signal with no parameter to a slot with, and give the parameter.
QxtMetaBall allowes you even to put expressions in. It requires the Qxt Meta Object Extender.
if you use qmake, just add CONFIG+=mox to your project file, it should automaticly invoce mox to create the nesacary mox_*  files, do NOT include those auto generated files yourself.

Usage:
\code
metaball(sender,SIGNAL(signal(int)),receiver,SLOT(slot(bool)),BALL(value>0));
\endcode

This will call receiver->slot(value>0) with the value emited by the signal sender->signal(int)
*/

///TODO:include classname in the signature to avoid colision


#define BALL(x) (QByteArray("Ball_")+(QByteArray(QByteArray(__FILE__)+QByteArray::number(__LINE__)).toBase64 ().replace("=","")))

class QxtMetaBall
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

