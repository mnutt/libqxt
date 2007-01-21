#include "QxtMetaBall.h"
bool QxtMetaBall::connect(QObject *sender,char *signal,QObject* receiver,char *slot,QByteArray ball)
		{
		if (!ball.startsWith("Ball_"))
			{qWarning("QxtMetaBall::connect: Use the BALL macro to define the expression.");
			return false;}

		QByteArray signal_b=QByteArray(signal);
		signal_b=signal_b.right( signal_b.size()-1);

		QByteArray slot_b=QByteArray(slot);
		slot_b=slot_b.right( slot_b.size()-1);

		return
		QObject::connect(sender,signal,QxtMetaBall::MetaTable(),"1"+ball+"_"+signal_b)
			&&
		QObject::connect(QxtMetaBall::MetaTable(),"2"+ball+"_"+slot_b,receiver,slot);
		}




bool QxtMetaBall::disconnect(QObject *sender,char *signal,QObject* receiver,char *slot,QByteArray ball)
		{
		if (!ball.startsWith("Ball_"))
			{qWarning("QxtMetaBall::disconnect: Use the BALL macro to define the expression.");
			return false;}

		QByteArray signal_b=QByteArray(signal);
		signal_b=signal_b.right( signal_b.size()-1);

		QByteArray slot_b=QByteArray(slot);
		slot_b=slot_b.right( slot_b.size()-1);

		return
		QObject::disconnect(sender,signal,QxtMetaBall::MetaTable(),"1"+ball+"_"+signal_b)
			&&
		QObject::disconnect(QxtMetaBall::MetaTable(),"2"+ball+"_"+slot_b,receiver,slot);
		}

