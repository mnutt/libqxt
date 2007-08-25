#include <QTest>
#include <QObject>
#include <QxtMetaObject>
#include <QSignalSpy>

class QxtMetaObjectTest: public QObject
{
    Q_OBJECT 

signals:
    void say(QString);
    void doit();

private slots:
    void readwrite()
    {
        QxtMetaObject::connect(this, SIGNAL(doit()), QxtMetaObject::bind(this, SLOT(say(QString)), Q_ARG(QString,"hello")));
        QSignalSpy spy(this, SIGNAL(say(QString)));
        emit(doit());
        QVERIFY2 (spy.count()> 0, "no signal received" );
        QVERIFY2 (spy.count()< 2, "wtf, two signals received?" );


        QList<QVariant> arguments = spy.takeFirst();
        QVERIFY2(arguments.at(0).toString()=="hello","argument missmatch");

    }

};



QTEST_MAIN(QxtMetaObjectTest)
#include "main.moc"

