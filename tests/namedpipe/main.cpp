/** ***** namedpipe loopback test ******/
#include <QxtNamedPipe>
#include <QTest>
#include <QSignalSpy>
#include <QBuffer>
#include <QDebug>
#include <QByteArray>

class QxtnamedPipeTest: public QObject
	{
	Q_OBJECT 
	private slots:
		void loopback()
			{ 
			QxtNamedPipe out("helloiamapipe");
			QVERIFY2(out.open(QIODevice::WriteOnly),"open failed");
			QxtNamedPipe in("helloiamapipe");
			QVERIFY2(in.open(QIODevice::ReadOnly),"open failed");

			QSignalSpy spyr(&in, SIGNAL(readyRead()));

                        out.write("hello");
                        QString readall=in.readAll();
                        qDebug()<<"output:"<<readall;
                        QVERIFY2(readall=="hello","output not mathing input");
			QVERIFY2 (spyr.count()> 0, "not emitting readyRead" );
			}

	signals:
		void wave();
		void counterwave();
 };



QTEST_MAIN(QxtnamedPipeTest)
#include "main.moc"
