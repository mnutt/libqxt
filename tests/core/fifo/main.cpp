#include <QCoreApplication>
#include <QxtFifo>
#include <QTest>
#include <QSignalSpy>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

class QxtFifoPipeTest: public QObject
{
    Q_OBJECT 
        private slots:
        void initTestCase()
        {
            io= new QxtFifo;
        }

    void readwrite()
    { 
        QDataStream w(io);
        w << QString("hello");
        w << 34;
        QString str;
        int i;
        QDataStream r(io);
        r >> str;
        r >> i;
        QVERIFY2(i==34,"output not matching input");
        QVERIFY2(str==QString("hello"),"output not mathing input");
    }

    void readyread()
    {
        QSignalSpy spyr(io, SIGNAL(readyRead()));
        io->write("hello");
        QCoreApplication::processEvents();
        QVERIFY2 (spyr.count()> 0, "not emitting readyRead" );
        io->readAll();
    }


    void size()
    {
        QByteArray data("askdoamsdoiasmdpoeiowaopimwaioemfowefnwaoief");
        QVERIFY(io->write(data)==data.size());
        QVERIFY(io->bytesAvailable()==data.size());
        io->readAll();
        QVERIFY(io->bytesAvailable()==0);
    }


    void cleanupTestCase()
    {
        delete(io);
    }




    private:
    QxtFifo * io;
};

QTEST_MAIN(QxtFifoPipeTest)
#include "main.moc"
