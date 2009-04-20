#include <QtTest>
#include <QtCore> //krazy:exclude=qxtincludes
#include <QxtModelSerializer>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>

class tst_QxtModelSerializer : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void serializationTest();
    void sanityTest();

private:
    bool copyModel(QAbstractItemModel* src, QAbstractItemModel* dst);
    bool compareModels(const QAbstractItemModel* a, const QAbstractItemModel* b, const QModelIndex& ai = QModelIndex(), const QModelIndex &bi = QModelIndex()) const;
};

void tst_QxtModelSerializer::initTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    QVERIFY(db.open());

    QSqlQuery query;
    query.exec("create table person (id int primary key, "
               "firstname varchar(20), lastname varchar(20))");
    query.exec("insert into person values(101, 'Danny', 'Young')");
    query.exec("insert into person values(102, 'Christine', 'Holand')");
    query.exec("insert into person values(103, 'Lars', 'Gordon')");
    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

    query.exec("create table offices (id int primary key,"
                                             "imagefile int,"
                                             "location varchar(20),"
                                             "country varchar(20),"
                                             "description varchar(100))");
    query.exec("insert into offices "
               "values(0, 0, 'Oslo', 'Norway',"
               "'Oslo is home to more than 500 000 citizens and has a "
               "lot to offer.It has been called \"The city with the big "
               "heart\" and this is a nickname we are happy to live up to.')");
    query.exec("insert into offices "
               "values(1, 1, 'Brisbane', 'Australia',"
               "'Brisbane is the capital of Queensland, the Sunshine State, "
               "where it is beautiful one day, perfect the next.  "
               "Brisbane is Australia''s 3rd largest city, being home "
               "to almost 2 million people.')");
    query.exec("insert into offices "
               "values(2, 2, 'Redwood City', 'US',"
               "'You find Redwood City in the heart of the Bay Area "
               "just north of Silicon Valley. The largest nearby city is "
               "San Jose which is the third largest city in California "
               "and the 10th largest in the US.')");
    query.exec("insert into offices "
               "values(3, 3, 'Berlin', 'Germany',"
               "'Berlin, the capital of Germany is dynamic, cosmopolitan "
               "and creative, allowing for every kind of lifestyle. "
               "East meets West in the metropolis at the heart of a "
               "changing Europe.')");
    query.exec("insert into offices "
               "values(4, 4, 'Munich', 'Germany',"
               "'Several technology companies are represented in Munich, "
               "and the city is often called the \"Bavarian Silicon Valley\". "
               "The exciting city is also filled with culture, "
               "art and music. ')");
    query.exec("insert into offices "
               "values(5, 5, 'Beijing', 'China',"
               "'Beijing as a capital city has more than 3000 years of "
               "history. Today the city counts 12 million citizens, and "
               "is the political, economic and cultural centre of China.')");
}

void tst_QxtModelSerializer::serializationTest()
{
    QSqlTableModel srcPersonModel;
    srcPersonModel.setTable("person");
    srcPersonModel.select();
    QStandardItemModel dstPersonModel;

    QVERIFY(copyModel(&srcPersonModel, &dstPersonModel));
    QVERIFY(compareModels(&srcPersonModel, &dstPersonModel));

    QSqlTableModel srcOfficesModel;
    srcOfficesModel.setTable("offices");
    srcOfficesModel.select();
    QSqlTableModel dstOfficesModel;
    srcOfficesModel.setTable("offices2");

    QVERIFY(copyModel(&srcOfficesModel, &dstOfficesModel));
    QVERIFY(compareModels(&srcOfficesModel, &dstOfficesModel));

    QStandardItemModel srcTreeModel;
    QStandardItem *parentItem = srcTreeModel.invisibleRootItem();
    for (int i = 0; i < 4; ++i) {
        QStandardItem* item = new QStandardItem(QString("item %0").arg(i));
        parentItem->appendRow(item);
        parentItem = item;
    }
    QStandardItemModel dstTreeModel;

    QVERIFY(copyModel(&srcTreeModel, &dstTreeModel));
    QVERIFY(compareModels(&srcTreeModel, &dstTreeModel));
}

void tst_QxtModelSerializer::sanityTest()
{
    QxtModelSerializer serializer;
    QVERIFY(!serializer.model());

    QCOMPARE(serializer.saveModel(), QByteArray());
    QCOMPARE(serializer.restoreModel(QByteArray()), false);
}

bool tst_QxtModelSerializer::copyModel(QAbstractItemModel* src, QAbstractItemModel* dst)
{
    QxtModelSerializer serializer(src);
    QByteArray data = serializer.saveModel();
    serializer.setModel(dst);
    return serializer.restoreModel(data);
}

bool tst_QxtModelSerializer::compareModels(const QAbstractItemModel* a, const QAbstractItemModel* b, const QModelIndex& ai, const QModelIndex &bi) const
{
    QMap<int, QVariant> ad = a->itemData(ai);
    QMap<int, QVariant> bd = b->itemData(bi);
    ad.remove(31); // because of QStandardItemModel
    bd.remove(31); // because of QStandardItemModel
    //if (ad != bd)
    //{
        //qDebug() << ad << bd;
        //return false;
    //}
    if (a->rowCount(ai) != b->rowCount(bi))
        return false;
    if (a->columnCount(ai) != b->columnCount(bi))
        return false;

    for (int r = 0; r < a->rowCount(ai); ++r)
        for (int c = 0; c < a->columnCount(ai); ++c)
            return compareModels(a, b, a->index(r, c, ai), b->index(r, c, bi));

    return true;
}

QTEST_MAIN(tst_QxtModelSerializer)
#include "tst_modelserializer.moc"
