/** ***** QxtRPCPeer loopback test ******/
#include <QxtRPCPeer>
#include <QxtNamedPipe>
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
			QxtNamedPipe out("helloiamapipe");
			QVERIFY2(out.open(QIODevice::ReadWrite),"open failed");
			QxtRPCPeer peer(&out);
  			QVERIFY2(peer.attachSignal (this, SIGNAL(wave())),"cannot attach signal");

			QxtNamedPipe in("helloiamapipe");
			QVERIFY2(in.open(QIODevice::ReadWrite),"open failed");
			QxtRPCPeer peer2(&in);
 			QVERIFY2(peer2.attachSlot ( "wave",this, SLOT(counterwavesl())),"cannot attach slot"); 

			QSignalSpy spy(this, SIGNAL(counterwave()));
			QSignalSpy spyr(&in, SIGNAL(readyRead()));

 			emit(wave());

			QCoreApplication::processEvents ();
			QCoreApplication::processEvents ();


			QVERIFY2 (spyr.count()> 0, "buffer not emitting readyRead" );

			QVERIFY2 (spy.count()> 0, "no signal received" );
			QVERIFY2 (spy.count()< 2, "wtf, two signals received?" );

			QList<QVariant> arguments = spy.takeFirst();
			QVERIFY2(arguments.at(0).toString() == "world","argument screwed");
			}
 		void cleanupTestCase(){ }

	signals:
		void wave();
		void counterwave();
 };



QTEST_MAIN(RPCTest)
#include "main.moc"
