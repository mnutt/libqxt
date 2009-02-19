#include <QxtBdbTree>
#include <QTest>
#include <QDebug>
#include <QStringList>

class Test: public QObject
{
Q_OBJECT 
private slots:
    void begin()
    {
        db.open("test.db");
        db.clear();
    }
    void readRoot()
    {
        QVERIFY(db.root().value().size()==0);
    }
    void readInvalid()
    {
        QVERIFY(db.root().child().value().size()==0);
        QVERIFY(db.root().next().value().size()==0);
        QVERIFY(db.root().previous().value().size()==0);
        QVERIFY(db.root().parent().value().size()==0);
    }
    void append()
    {
        QVERIFY(db.root().append(QStringList()<<"asda"<<"asfg").isValid());
        QVERIFY(db.root().append(QStringList()<<"sh00"<<"xcv").append(QStringList()<<"vvvv").isValid());
    }
    void prepend()
    {
        QVERIFY(db.root().append(QStringList()<<"xylophon").prepend(QStringList()<<"you"<<"rock").isValid());
    }

    void read()
    {
        QVERIFY( (db.root().child()+1).child().value().at(0)=="vvvv");
        QVERIFY( (db.root().child()+2).value().at(1)=="rock");
    }
    void erasePersistance()
    {
        QxtBdbTreeIterator<QStringList> sib=db.root().child()+1;
        QVERIFY(sib.value().at(0)=="sh00");
//         QVERIFY(db.root().child().erase() == sib ); ///doesn't work yet
        QVERIFY(db.root().child().erase().value() == sib.value() );
        QVERIFY(sib.value().at(0)=="sh00");

        sib=db.root().child()+2;
        QVERIFY(sib.value().at(0)=="xylophon");
//         QVERIFY(db.root().child().erase() == sib ); ///doesn't work yet
        QVERIFY((db.root().child()+1).erase().value() == sib.value() );
        QVERIFY(sib.value().at(0)=="xylophon");
    }
    void end()
    {
    }

private:
    QxtBdbTree<QStringList> db;
};

QTEST_MAIN(Test)
#include "main.moc"
