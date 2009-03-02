#include <QtTest>
#include <QtCore> //krazy:exclude=qxtincludes
#include <QxtSlotMapper>
#include "sender.h"
#include "receiver.h"

class tst_QxtSlotMapper : public QObject
{
    Q_OBJECT

private slots:
    void intTest();
    void uintTest();
    void qlonglongTest();
    void qulonglongTest();
    void boolTest();
    void doubleTest();
    //void charTest(); "const char*" is not a meta type
    void byteArrayTest();
    void bitArrayTest();
    void stringTest();
    //void latin1StringTest(); "QLatin1String" is not a meta type
    void stringListTest();
    void qcharTest();
    void dateTest();
    void timeTest();
    void dateTimeTest();
    void listTest();
    void mapTest();
    void sizeTest();
    void sizeFTest();
    void pointTest();
    void pointFTest();
    void lineTest();
    void lineFTest();
    void rectTest();
    void rectFTest();
    void urlTest();
    void localeTest();
    void regExpTest();
    void globalColorTest();
};

void tst_QxtSlotMapper::intTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(intSignal(int)));
    mapper.connect(&sender2, SIGNAL(intSignal(int)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(1, &receiver1, SLOT(intSlot(int)));
    mapper.addMapping(2, &receiver2, SLOT(intSlot(int)));
    
    emit sender1.intSignal(1);
    QCOMPARE(receiver1.ints.value(0), 1);
    
    emit sender2.intSignal(2);
    QCOMPARE(receiver2.ints.at(0), 2);
}

void tst_QxtSlotMapper::uintTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(uintSignal(uint)));
    mapper.connect(&sender2, SIGNAL(uintSignal(uint)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(1, &receiver1, SLOT(uintSlot(uint)));
    mapper.addMapping(2, &receiver2, SLOT(uintSlot(uint)));
    
    emit sender1.uintSignal(1);
    QVERIFY(receiver1.uints.value(0) == 1);
    
    emit sender2.uintSignal(2);
    QVERIFY(receiver2.uints.at(0) == 2);
}

void tst_QxtSlotMapper::qlonglongTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(qlonglongSignal(qlonglong)));
    mapper.connect(&sender2, SIGNAL(qlonglongSignal(qlonglong)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(1, &receiver1, SLOT(qlonglongSlot(qlonglong)));
    mapper.addMapping(2, &receiver2, SLOT(qlonglongSlot(qlonglong)));
    
    emit sender1.qlonglongSignal(1);
    QVERIFY(receiver1.qlonglongs.value(0) == 1);
    
    emit sender2.qlonglongSignal(2);
    QVERIFY(receiver2.qlonglongs.at(0) == 2);
}

void tst_QxtSlotMapper::qulonglongTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(qulonglongSignal(qulonglong)));
    mapper.connect(&sender2, SIGNAL(qulonglongSignal(qulonglong)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(1, &receiver1, SLOT(qulonglongSlot(qulonglong)));
    mapper.addMapping(2, &receiver2, SLOT(qulonglongSlot(qulonglong)));
    
    emit sender1.qulonglongSignal(1);
    QVERIFY(receiver1.qulonglongs.value(0) == 1);
    
    emit sender2.qulonglongSignal(2);
    QVERIFY(receiver2.qulonglongs.at(0) == 2);
}

void tst_QxtSlotMapper::boolTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(boolSignal(bool)));
    mapper.connect(&sender2, SIGNAL(boolSignal(bool)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(true, &receiver1, SLOT(boolSlot(bool)));
    mapper.addMapping(false, &receiver2, SLOT(boolSlot(bool)));
    
    emit sender1.boolSignal(true);
    QCOMPARE(receiver1.bools.value(0), true);
    
    emit sender2.boolSignal(false);
    QCOMPARE(receiver2.bools.at(0), false);
}

void tst_QxtSlotMapper::doubleTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(doubleSignal(double)));
    mapper.connect(&sender2, SIGNAL(doubleSignal(double)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(1.1, &receiver1, SLOT(doubleSlot(double)));
    mapper.addMapping(2.2, &receiver2, SLOT(doubleSlot(double)));
    
    emit sender1.doubleSignal(1.1);
    QCOMPARE(receiver1.doubles.value(0), 1.1);
    
    emit sender2.doubleSignal(2.2);
    QCOMPARE(receiver2.doubles.at(0), 2.2);
}

/*
"const char*" is not a meta type
void tst_QxtSlotMapper::charTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(charSignal(const char*)));
    mapper.connect(&sender2, SIGNAL(charSignal(const char*)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping("foo", &receiver1, SLOT(charSlot(const char*)));
    mapper.addMapping("bar", &receiver2, SLOT(charSlot(const char*)));
    
    emit sender1.charSignal("foo");
    QCOMPARE(receiver1.chars.value(0), "foo");
    
    emit sender2.charSignal("bar");
    QCOMPARE(receiver2.chars.at(0), "bar");
}
*/

void tst_QxtSlotMapper::byteArrayTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(byteArraySignal(QByteArray)));
    mapper.connect(&sender2, SIGNAL(byteArraySignal(QByteArray)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QByteArray("foo"), &receiver1, SLOT(byteArraySlot(QByteArray)));
    mapper.addMapping(QByteArray("bar"), &receiver2, SLOT(byteArraySlot(QByteArray)));
    
    emit sender1.byteArraySignal("foo");
    QCOMPARE(receiver1.byteArrays.value(0), QByteArray("foo"));
    
    emit sender2.byteArraySignal("bar");
    QCOMPARE(receiver2.byteArrays.at(0), QByteArray("bar"));
}

void tst_QxtSlotMapper::bitArrayTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(bitArraySignal(QBitArray)));
    mapper.connect(&sender2, SIGNAL(bitArraySignal(QBitArray)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QBitArray(1, true), &receiver1, SLOT(bitArraySlot(QBitArray)));
    mapper.addMapping(QBitArray(2, false), &receiver2, SLOT(bitArraySlot(QBitArray)));
    
    emit sender1.bitArraySignal(QBitArray(1, true));
    QCOMPARE(receiver1.bitArrays.value(0), QBitArray(1, true));
    
    emit sender2.bitArraySignal(QBitArray(2, false));
    QCOMPARE(receiver2.bitArrays.at(0), QBitArray(2, false));
}

void tst_QxtSlotMapper::stringTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(stringSignal(QString)));
    mapper.connect(&sender2, SIGNAL(stringSignal(QString)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QString("foo"), &receiver1, SLOT(stringSlot(QString)));
    mapper.addMapping(QString("bar"), &receiver2, SLOT(stringSlot(QString)));
    
    emit sender1.stringSignal("foo");
    QCOMPARE(receiver1.strings.value(0), QString("foo"));
    
    emit sender2.stringSignal("bar");
    QCOMPARE(receiver2.strings.at(0), QString("bar"));
}

/*
"QLatin1String" is not a meta type
void tst_QxtSlotMapper::latin1StringTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(latin1StringSignal(QLatin1String)));
    mapper.connect(&sender2, SIGNAL(latin1StringSignal(QLatin1String)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QLatin1String("foo"), &receiver1, SLOT(latin1StringSlot(QLatin1String)));
    mapper.addMapping(QLatin1String("bar"), &receiver2, SLOT(latin1StringSlot(QLatin1String)));
    
    emit sender1.latin1StringSignal("foo");
    QCOMPARE(receiver1.latin1Strings.value(0), QLatin1String("foo"));
    
    emit sender2.latin1StringSignal("bar");
    QCOMPARE(receiver2.latin1Strings.at(0), QLatin1String("bar"));
}
*/

void tst_QxtSlotMapper::stringListTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(stringListSignal(QStringList)));
    mapper.connect(&sender2, SIGNAL(stringListSignal(QStringList)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QStringList("foo"), &receiver1, SLOT(stringListSlot(QStringList)));
    mapper.addMapping(QStringList("bar"), &receiver2, SLOT(stringListSlot(QStringList)));
    
    emit sender1.stringListSignal(QStringList("foo"));
    QCOMPARE(receiver1.stringLists.value(0), QStringList("foo"));
    
    emit sender2.stringListSignal(QStringList("bar"));
    QCOMPARE(receiver2.stringLists.at(0), QStringList("bar"));
}

void tst_QxtSlotMapper::qcharTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(qcharSignal(QChar)));
    mapper.connect(&sender2, SIGNAL(qcharSignal(QChar)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QChar('a'), &receiver1, SLOT(qcharSlot(QChar)));
    mapper.addMapping(QChar('b'), &receiver2, SLOT(qcharSlot(QChar)));
    
    emit sender1.qcharSignal(QChar('a'));
    QCOMPARE(receiver1.qchars.value(0), QChar('a'));
    
    emit sender2.qcharSignal(QChar('b'));
    QCOMPARE(receiver2.qchars.value(0), QChar('b'));
}

void tst_QxtSlotMapper::dateTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(dateSignal(QDate)));
    mapper.connect(&sender2, SIGNAL(dateSignal(QDate)));
    
    QDate date1 = QDate::currentDate().addDays(1);
    QDate date2 = QDate::currentDate().addDays(2);
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(date1, &receiver1, SLOT(dateSlot(QDate)));
    mapper.addMapping(date2, &receiver2, SLOT(dateSlot(QDate)));
    
    emit sender1.dateSignal(date1);
    QCOMPARE(receiver1.dates.value(0), date1);
    
    emit sender2.dateSignal(date2);
    QCOMPARE(receiver2.dates.value(0), date2);
}

void tst_QxtSlotMapper::timeTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(timeSignal(QTime)));
    mapper.connect(&sender2, SIGNAL(timeSignal(QTime)));
    
    QTime time1 = QTime::currentTime().addSecs(1);
    QTime time2 = QTime::currentTime().addSecs(2);
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(time1, &receiver1, SLOT(timeSlot(QTime)));
    mapper.addMapping(time2, &receiver2, SLOT(timeSlot(QTime)));
    
    emit sender1.timeSignal(time1);
    QCOMPARE(receiver1.times.value(0), time1);
    
    emit sender2.timeSignal(time2);
    QCOMPARE(receiver2.times.value(0), time2);
}

void tst_QxtSlotMapper::dateTimeTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(dateTimeSignal(QDateTime)));
    mapper.connect(&sender2, SIGNAL(dateTimeSignal(QDateTime)));
    
    QDateTime dateTime1 = QDateTime::currentDateTime().addYears(1);
    QDateTime dateTime2 = QDateTime::currentDateTime().addYears(2);
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(dateTime1, &receiver1, SLOT(dateTimeSlot(QDateTime)));
    mapper.addMapping(dateTime2, &receiver2, SLOT(dateTimeSlot(QDateTime)));
    
    emit sender1.dateTimeSignal(dateTime1);
    QCOMPARE(receiver1.dateTimes.value(0), dateTime1);
    
    emit sender2.dateTimeSignal(dateTime2);
    QCOMPARE(receiver2.dateTimes.value(0), dateTime2);
}

void tst_QxtSlotMapper::listTest()
{
}

void tst_QxtSlotMapper::mapTest()
{
}

void tst_QxtSlotMapper::sizeTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(sizeSignal(QSize)));
    mapper.connect(&sender2, SIGNAL(sizeSignal(QSize)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QSize(1,1), &receiver1, SLOT(sizeSlot(QSize)));
    mapper.addMapping(QSize(2,2), &receiver2, SLOT(sizeSlot(QSize)));
    
    emit sender1.sizeSignal(QSize(1,1));
    QCOMPARE(receiver1.sizes.value(0), QSize(1,1));
    
    emit sender2.sizeSignal(QSize(2,2));
    QCOMPARE(receiver2.sizes.value(0), QSize(2,2));
}

void tst_QxtSlotMapper::sizeFTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(sizeFSignal(QSizeF)));
    mapper.connect(&sender2, SIGNAL(sizeFSignal(QSizeF)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QSizeF(1.1,1.1), &receiver1, SLOT(sizeFSlot(QSizeF)));
    mapper.addMapping(QSizeF(2.2,2.2), &receiver2, SLOT(sizeFSlot(QSizeF)));
    
    emit sender1.sizeFSignal(QSizeF(1.1,1.1));
    QCOMPARE(receiver1.sizeFs.value(0), QSizeF(1.1,1.1));
    
    emit sender2.sizeFSignal(QSizeF(2.2,2.2));
    QCOMPARE(receiver2.sizeFs.value(0), QSizeF(2.2,2.2));
}

void tst_QxtSlotMapper::pointTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(pointSignal(QPoint)));
    mapper.connect(&sender2, SIGNAL(pointSignal(QPoint)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QPoint(1,1), &receiver1, SLOT(pointSlot(QPoint)));
    mapper.addMapping(QPoint(2,2), &receiver2, SLOT(pointSlot(QPoint)));
    
    emit sender1.pointSignal(QPoint(1,1));
    QCOMPARE(receiver1.points.value(0), QPoint(1,1));
    
    emit sender2.pointSignal(QPoint(2,2));
    QCOMPARE(receiver2.points.value(0), QPoint(2,2));
}

void tst_QxtSlotMapper::pointFTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(pointFSignal(QPointF)));
    mapper.connect(&sender2, SIGNAL(pointFSignal(QPointF)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QPointF(1.1,1.1), &receiver1, SLOT(pointFSlot(QPointF)));
    mapper.addMapping(QPointF(2.2,2.2), &receiver2, SLOT(pointFSlot(QPointF)));
    
    emit sender1.pointFSignal(QPointF(1.1,1.1));
    QCOMPARE(receiver1.pointFs.value(0), QPointF(1.1,1.1));
    
    emit sender2.pointFSignal(QPointF(2.2,2.2));
    QCOMPARE(receiver2.pointFs.value(0), QPointF(2.2,2.2));
}

void tst_QxtSlotMapper::lineTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(lineSignal(QLine)));
    mapper.connect(&sender2, SIGNAL(lineSignal(QLine)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QLine(1,1,1,1), &receiver1, SLOT(lineSlot(QLine)));
    mapper.addMapping(QLine(2,2,2,2), &receiver2, SLOT(lineSlot(QLine)));
    
    emit sender1.lineSignal(QLine(1,1,1,1));
    QCOMPARE(receiver1.lines.value(0), QLine(1,1,1,1));
    
    emit sender2.lineSignal(QLine(2,2,2,2));
    QCOMPARE(receiver2.lines.value(0), QLine(2,2,2,2));
}

void tst_QxtSlotMapper::lineFTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(lineFSignal(QLineF)));
    mapper.connect(&sender2, SIGNAL(lineFSignal(QLineF)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QLineF(1.1,1.1,1.1,1.1), &receiver1, SLOT(lineFSlot(QLineF)));
    mapper.addMapping(QLineF(2.2,2.2,2.2,2.2), &receiver2, SLOT(lineFSlot(QLineF)));
    
    emit sender1.lineFSignal(QLineF(1.1,1.1,1.1,1.1));
    QCOMPARE(receiver1.lineFs.value(0), QLineF(1.1,1.1,1.1,1.1));
    
    emit sender2.lineFSignal(QLineF(2.2,2.2,2.2,2.2));
    QCOMPARE(receiver2.lineFs.value(0), QLineF(2.2,2.2,2.2,2.2));
}

void tst_QxtSlotMapper::rectTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(rectSignal(QRect)));
    mapper.connect(&sender2, SIGNAL(rectSignal(QRect)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QRect(1,1,1,1), &receiver1, SLOT(rectSlot(QRect)));
    mapper.addMapping(QRect(2,2,2,2), &receiver2, SLOT(rectSlot(QRect)));
    
    emit sender1.rectSignal(QRect(1,1,1,1));
    QCOMPARE(receiver1.rects.value(0), QRect(1,1,1,1));
    
    emit sender2.rectSignal(QRect(2,2,2,2));
    QCOMPARE(receiver2.rects.value(0), QRect(2,2,2,2));
}

void tst_QxtSlotMapper::rectFTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(rectFSignal(QRectF)));
    mapper.connect(&sender2, SIGNAL(rectFSignal(QRectF)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QRectF(1.1,1.1,1.1,1.1), &receiver1, SLOT(rectFSlot(QRectF)));
    mapper.addMapping(QRectF(2.2,2.2,2.2,2.2), &receiver2, SLOT(rectFSlot(QRectF)));
    
    emit sender1.rectFSignal(QRectF(1.1,1.1,1.1,1.1));
    QCOMPARE(receiver1.rectFs.value(0), QRectF(1.1,1.1,1.1,1.1));
    
    emit sender2.rectFSignal(QRectF(2.2,2.2,2.2,2.2));
    QCOMPARE(receiver2.rectFs.value(0), QRectF(2.2,2.2,2.2,2.2));
}

void tst_QxtSlotMapper::urlTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(urlSignal(QUrl)));
    mapper.connect(&sender2, SIGNAL(urlSignal(QUrl)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QUrl("1"), &receiver1, SLOT(urlSlot(QUrl)));
    mapper.addMapping(QUrl("2"), &receiver2, SLOT(urlSlot(QUrl)));
    
    emit sender1.urlSignal(QUrl("1"));
    QCOMPARE(receiver1.urls.value(0), QUrl("1"));
    
    emit sender2.urlSignal(QUrl("2"));
    QCOMPARE(receiver2.urls.value(0), QUrl("2"));
}

void tst_QxtSlotMapper::localeTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(localeSignal(QLocale)));
    mapper.connect(&sender2, SIGNAL(localeSignal(QLocale)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QLocale("en"), &receiver1, SLOT(localeSlot(QLocale)));
    mapper.addMapping(QLocale("fi"), &receiver2, SLOT(localeSlot(QLocale)));
    
    emit sender1.localeSignal(QLocale("en"));
    QCOMPARE(receiver1.locales.value(0), QLocale("en"));
    
    emit sender2.localeSignal(QLocale("fi"));
    QCOMPARE(receiver2.locales.value(0), QLocale("fi"));
}

void tst_QxtSlotMapper::regExpTest()
{
    QxtSlotMapper mapper;
    
    Sender sender1;
    Sender sender2;
    mapper.connect(&sender1, SIGNAL(regExpSignal(QRegExp)));
    mapper.connect(&sender2, SIGNAL(regExpSignal(QRegExp)));
    
    Receiver receiver1;
    Receiver receiver2;
    mapper.addMapping(QRegExp("foo"), &receiver1, SLOT(regExpSlot(QRegExp)));
    mapper.addMapping(QRegExp("bar"), &receiver2, SLOT(regExpSlot(QRegExp)));
    
    emit sender1.regExpSignal(QRegExp("foo"));
    QCOMPARE(receiver1.regExps.value(0), QRegExp("foo"));
    
    emit sender2.regExpSignal(QRegExp("bar"));
    QCOMPARE(receiver2.regExps.value(0), QRegExp("bar"));
}

void tst_QxtSlotMapper::globalColorTest()
{
}

QTEST_MAIN(tst_QxtSlotMapper)
#include "tst_qxtslotmapper.moc"
