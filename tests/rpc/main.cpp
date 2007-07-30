/** ***** QxtRPCPeer loopback test ******/
#include <QxtRPCPeer>
#include <QxtFifo>
#include <QCoreApplication>
#include <QTest>
#include <QSignalSpy>
#include <QBuffer>
#include <QDebug>
#include <QByteArray>

class RPCTest: public QObject
	{
	Q_OBJECT
	private:
		QxtRPCPeer* peer;
 
	private slots:
 		void initTestCase(){ }



		void loopback()
			{ 
			QxtFifo io;
			QxtRPCPeer peer(&io);
  			QVERIFY2(peer.attachSignal (this, SIGNAL(  wave  ( QString ) ) ),"cannot attach signal");
 			QVERIFY2(peer.attachSlot (  SIGNAL(   wave (  QString  )   ),this, SIGNAL( counterwave(QString  )) ),"cannot attach slot"); 

			QSignalSpy spy(this, SIGNAL(counterwave(QString)));
			QSignalSpy spyr(&io, SIGNAL(readyRead()));

 			emit(wave("world"));

			QCoreApplication::processEvents ();
			QCoreApplication::processEvents ();


			QVERIFY2 (spyr.count()> 0, "buffer not emitting readyRead" );

			QVERIFY2 (spy.count()> 0, "no signal received" );
			QVERIFY2 (spy.count()< 2, "wtf, two signals received?" );

			QList<QVariant> arguments = spy.takeFirst();
			QVERIFY2(arguments.at(0).toString()=="world","argument missmatch");
			}
 		void cleanupTestCase(){ }

	signals:
		void wave(QString);
		void counterwave(QString);
 };



QTEST_MAIN(RPCTest)
#include "main.moc"
