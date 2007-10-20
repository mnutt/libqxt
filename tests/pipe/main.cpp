#include <QxtPipe>
#include <QTest>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

class QxtPipeTest: public QObject
{
Q_OBJECT 
private slots:
    void readwrite()
    {
        QxtPipe p1;
        QxtPipe p2;
        p1|p2;
        p1.write("hi");
        QVERIFY(p2.readAll()=="hi");
    }
    void bidirectional()
    {
        QxtPipe p1;
        QxtPipe p2;
        p1|p2;
        p2|p1;
        p1.write("hi");
        QVERIFY(p2.readAll()=="hi");
        QVERIFY(p2.readAll()==QString());
    }
};

QTEST_MAIN(QxtPipeTest)
#include "main.moc"
