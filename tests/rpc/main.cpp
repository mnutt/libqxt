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

	public slots:
		 void counterwavesl()
			{
			qDebug("hey");
			emit(counterwave());
			}

 
	private slots:
 		void initTestCase(){ }



		void loopback()
			{ 
			QxtFifo io;
			QxtRPCPeer peer(&io);
  			QVERIFY2(peer.attachSignal (this, SIGNAL(  wave  ( ) ) ),"cannot attach signal");
 			QVERIFY2(peer.attachSlot (  SIGNAL(   wave (    )   ),this, SIGNAL( counterwave()) ),"cannot attach slot"); 

			QSignalSpy spy(this, SIGNAL(counterwave()));
			QSignalSpy spyr(&io, SIGNAL(readyRead()));

 			emit(wave());

			QCoreApplication::processEvents ();
			QCoreApplication::processEvents ();


			QVERIFY2 (spyr.count()> 0, "buffer not emitting readyRead" );

			QVERIFY2 (spy.count()> 0, "no signal received" );
			QVERIFY2 (spy.count()< 2, "wtf, two signals received?" );

			QList<QVariant> arguments = spy.takeFirst();
			}
 		void cleanupTestCase(){ }

	signals:
		void wave();
		void counterwave();
 };



QTEST_MAIN(RPCTest)
#include "main.moc"
