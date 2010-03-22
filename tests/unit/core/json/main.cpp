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
        QCOMPARE(QxtJSON::parse("5123").toInt(),5123);
        QCOMPARE(QxtJSON::parse("1.5").toDouble(),1.5);
    }

	void parseWhitespace(){
        QCOMPARE(QxtJSON::parse("\r\n 51235656          \r\n").toInt(),51235656);
        QCOMPARE(QxtJSON::parse("\r\n [         51235656 ] ").toList(),QVariantList()<<51235656);

        QVariantMap e;
        e["bla"]="fish";
        e["foo"]=5;
        e["boo"]=false;
        QCOMPARE(QxtJSON::parse(" { \"bla\": \"fish\"    ,    \"boo\":false ,\n\"foo\": 5  }\n" ),QVariant(e));
    }

	void same(){
        QVariantList e;
        e<<"fish"<<true<<QVariant()<<"bla"<<false<<6.5;
        QCOMPARE(QxtJSON::parse(QxtJSON::stringify(e)),QVariant(e));
	}


	void regressXenakios(){
        QVariant e=QxtJSON::parse("{\"apina\":\"ripulia!\",\"doctype\":\"QtCDP WorkSpace\",\"processinghistory\":[{\"infilename\":\"H:/Samples from net/Berklee44v8/Berklee44v8/aluminum2.wav\",\"itemname\":\"aluminum2.wav\",\"itemtag\":\"inputfile\",\"tse\":5.62246,\"tss\":5.08163},{\"infilename\":\"H:/Samples from net/Berklee44v8/Berklee44v8/aluminum3.wav\",\"itemname\":\"aluminum3.wav\",\"itemtag\":\"inputfile\"},{\"infilename\":\"H:/Samples from net/Berklee44v8/Berklee44v8/asprin_crinkle_1.wav\",\"itemname\":\"asprin_crinkle_1.wav\",\"itemtag\":\"inputfile\",\"tse\":0.593006,\"tss\":0.255667},{\"infilename\":\"H:/Samples from net/Berklee44v8/Berklee44v8/asprin_crinkle_2.wav\",\"itemname\":\"asprin_crinkle_2.wav\",\"itemtag\":\"inputfile\",\"tse\":1.66739,\"tss\":1.53128}]}");
        QVERIFY(!e.isNull());
    }


};

QTEST_MAIN(QxtJSONTest)
#include "main.moc"
