/** ***** QxtRPCPeer loopback test ******/
#include <QxtRPCPeer>
#include <qxtfifo.h>
#include <QCoreApplication>
#include <QTest>
#include <QThread>
#include <QSignalSpy>
#include <QBuffer>
#include <QDebug>
#include <QByteArray>
#include <QTcpSocket>

class RPCTest: public QObject
{
    Q_OBJECT
public:
    RPCTest() : client_id(0) {}

private:
    quint64 client_id;

signals:
    void wave(QString);
    void counterwave(QString);
    void networkedwave(quint64,QString);


private slots:
    void initTestCase()
    {
        client_id = 0;
    }

    void clientConnected(quint64 id) 
    {
        client_id = id;
    }

    void serverError(QAbstractSocket::SocketError e)
    {
        if (e != QAbstractSocket::RemoteHostClosedError) {
            qCritical("socket error: %i", e);
            QVERIFY2(false, "socket error");
        }
    }
        
    void loopback()
    {
        QxtRPCService peer(new QxtFifo, 0);
        QVERIFY2(peer.attachSignal (this, SIGNAL(  wave  ( QString ) ) ),"cannot attach signal");
        QVERIFY2(peer.attachSlot (  SIGNAL(   wave (  QString  )   ),this, SIGNAL( counterwave(QString  )) ),"cannot attach slot");

        QSignalSpy spy(this, SIGNAL(counterwave(QString)));
        QSignalSpy spyr(peer.device(), SIGNAL(readyRead()));

        emit(wave("world"));

        QCoreApplication::processEvents ();
        QCoreApplication::processEvents ();

        QVERIFY2 (spyr.count()> 0, "buffer not emitting readyRead" );

        QVERIFY2 (spy.count()> 0, "no signal received" );
        QVERIFY2 (spy.count()< 2, "wtf, two signals received?" );

        QList<QVariant> arguments = spy.takeFirst();
        QVERIFY2(arguments.at(0).toString()=="world","argument missmatch");
    }
    void directcall()
    {
        QxtRPCService peer(new QxtFifo, 0);
        QVERIFY2(peer.attachSlot (  SIGNAL(   wave (  QString  )   ),this, SIGNAL( counterwave(QString  )) ),"cannot attach slot");

        QSignalSpy spy(this, SIGNAL(counterwave(QString)));
        QSignalSpy spyr(peer.device(), SIGNAL(readyRead()));
        peer.call(SIGNAL(wave   ( QString   )  ),QString("world"));

        QCoreApplication::processEvents ();
        QCoreApplication::processEvents ();


        QVERIFY2 (spyr.count()> 0, "buffer not emitting readyRead" );

        QVERIFY2 (spy.count()> 0, "no signal received" );
        QVERIFY2 (spy.count()< 2, "wtf, two signals received?" );

        QList<QVariant> arguments = spy.takeFirst();
        QVERIFY2(arguments.at(0).toString()=="world","argument missmatch");
    }

    void TcpServerIo()
    {
        QxtRPCPeer server;
        QVERIFY2(server.attachSlot (SIGNAL(wave(QString)),this,SIGNAL(networkedwave(quint64,QString))),"cannot attach slot");


        QVERIFY(server.listen (QHostAddress::LocalHost, 23444));


        QxtRPCPeer client;
        client.connect (QHostAddress::LocalHost, 23444);
        QVERIFY(qobject_cast<QTcpSocket*>(client.device())->waitForConnected ( 30000 ));


        QSignalSpy spy(this, SIGNAL(networkedwave(quint64,QString)));
        client.call(SIGNAL(wave(QString)),QString("world"));


        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();


        QVERIFY2 (spy.count()> 0, "no signal received" );
        QVERIFY2 (spy.count()< 2, "wtf, two signals received?" );

        QList<QVariant> arguments = spy.takeFirst();
        QVERIFY2(arguments.at(1).toString()=="world","argument missmatch");
    }

    void TcpServerIoDisconnect()
    {
        // check that disconnect from server doesn't crash client (which it did in 0.5.1)

        QxtRPCPeer server;
        QVERIFY2(connect(&server, SIGNAL(clientConnected(quint64)),this,SLOT(clientConnected(quint64))),"cannot connect");
        QVERIFY2(connect(&server, SIGNAL(serverError(QAbstractSocket::SocketError)),this,SLOT(serverError(QAbstractSocket::SocketError))),"cannot connect");
        QVERIFY(server.listen (QHostAddress::LocalHost, 23444));

        QVERIFY(client_id == 0);

        QxtRPCPeer client;
        client.connect (QHostAddress::LocalHost, 23444);
        QVERIFY2(connect(&client, SIGNAL(serverError(QAbstractSocket::SocketError)),this,SLOT(serverError(QAbstractSocket::SocketError))),"cannot connect");
        QVERIFY(qobject_cast<QTcpSocket*>(client.device())->waitForConnected ( 30000 ));

        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();
        QCoreApplication::processEvents ();
        QCoreApplication::processEvents ();

        QVERIFY(client.isClient());
        QVERIFY(client_id != 0);
  
        server.disconnectClient(client_id);

        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();
        QThread::yieldCurrentThread();
        QCoreApplication::processEvents ();


        QVERIFY(server.isServer());
        QVERIFY(!client.isClient());
    }

    void cleanupTestCase()
    {}
};

QTEST_MAIN(RPCTest)
#include "main.moc"
