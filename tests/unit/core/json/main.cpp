#include <QxtJSON>
#include <QTest>
#include <QDebug>

class QxtJSONTest: public QObject{
    Q_OBJECT;
private slots:
    void initTestCase(){
    }

	void stringifyBasic(){
        QCOMPARE(QxtJSON::stringify((int)4),QString("4"));
        QCOMPARE(QxtJSON::stringify(false),QString("false"));
        QCOMPARE(QxtJSON::stringify(true),QString("true"));
        QCOMPARE(QxtJSON::stringify(QVariant()),QString("null"));
        QCOMPARE(QxtJSON::stringify("hi"),QString("\"hi\""));
        QCOMPARE(QxtJSON::stringify("hi"),QString("\"hi\""));
        QCOMPARE(QxtJSON::stringify(0.4),QString("0.4"));
        QCOMPARE(QxtJSON::stringify(QVariantList()<<4),QString("[4]"));
        QCOMPARE(QxtJSON::stringify(QVariantList()),QString("[]"));
	}
    void stringifyList(){
        QVariantList e;
        e<<"fish";
        e<<5;
        e<<false;
        QCOMPARE(QxtJSON::stringify(e),QString("[\"fish\",5,false]"));
    }
    void stringifyMap(){
        QVariantMap e;
        e["bla"]="fish";
        e["foo"]=5;
        e["boo"]=false;
        QCOMPARE(QxtJSON::stringify(e),QString("{\"bla\":\"fish\",\"boo\":false,\"foo\":5}"));
    }
	void parseLiteral(){
        QCOMPARE(QxtJSON::parse("0.5").toDouble(),0.5);
    }
	void same(){
        QVariantList e;
        e<<"fish"<<true<<QVariant()<<"bla"<<false;
        QCOMPARE(QxtJSON::parse(QxtJSON::stringify(e)),QVariant(e));
	}
};

QTEST_MAIN(QxtJSONTest)
#include "main.moc"
