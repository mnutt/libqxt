#include <QxtBdbHash>
#include <QTest>
#include <QDebug>
#include <QStringList>

class Test: public QObject
{
Q_OBJECT 
private slots:
    void begin()
    {
        db = new QxtBdbHash<qreal,QStringList>("test.db");
    }
    void insert()
    {
        QVERIFY(db->insert(454.332,QStringList()<<"hello"<<"how are you?"));
        QVERIFY(db->insert(235,QStringList()<<"hey"<<"how's it going?"));
        QVERIFY(db->insert(234,QStringList()<<"jo"<<"sup?"));
    }
    void contains()
    {
        QVERIFY(db->contains(235));
        QVERIFY(!db->contains(34.24));
    }
    void read()
    {
        QxtBdbHash<qreal,QStringList>  d=*db;
        QVERIFY(d[235].at(1)=="how's it going?");
    }
    void clear()
    {
        QVERIFY(db->contains(235));
        db->clear();
        QVERIFY(!db->contains(235));
    }
    void end()
    {
        delete db;
    }

private:
    QxtBdbHash<qreal,QStringList> * db;
};

QTEST_MAIN(Test)
#include "main.moc"
