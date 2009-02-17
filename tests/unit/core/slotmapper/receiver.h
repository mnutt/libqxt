#ifndef RECEIVER_H
#define RECEIVER_H

#include <QtCore> //krazy:exclude=qxtincludes

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver() { }

public slots:
    void intSlot(int val) { ints << val; }
    void uintSlot(uint val) { uints << val; }
    void qlonglongSlot(qlonglong val) { qlonglongs << val; }
    void qulonglongSlot(qulonglong val) { qulonglongs << val; }
    void boolSlot(bool val) { bools << val; }
    void doubleSlot(double val) { doubles << val; }
    //void charSlot(const char* val) { chars << val; } "const char*" is not a meta type
    void byteArraySlot(const QByteArray& val) { byteArrays << val; }
    void bitArraySlot(const QBitArray& val) { bitArrays << val; }
    void stringSlot(const QString& val) { strings << val; }
    //void latin1StringList(const QLatin1String& val) { latin1Strings << val; } "QLatin1String" is not a meta type
    void stringListSlot(const QStringList& val) { stringLists << val; }
    void qcharSlot(const QChar& val) { qchars << val; }
    void dateSlot(const QDate& val) { dates << val; }
    void timeSlot(const QTime& val) { times << val; }
    void dateTimeSlot(const QDateTime& val) { dateTimes << val; }
    void listSlot(const QVariantList& val) { lists << val; }
    void mapSlot(const QVariantMap& val) { maps << val; }
    void sizeSlot(const QSize& val) { sizes << val; }
    void sizeFSlot(const QSizeF& val) { sizeFs << val; }
    void pointSlot(const QPoint& val) { points << val; }
    void pointFSlot(const QPointF& val) { pointFs << val; }
    void lineSlot(const QLine& val) { lines << val; }
    void lineFSlot(const QLineF& val) { lineFs << val; }
    void rectSlot(const QRect& val) { rects << val; }
    void rectFSlot(const QRectF& val) { rectFs << val; }
    void urlSlot(const QUrl& val) { urls << val; }
    void localeSlot(const QLocale& val) { locales << val; }
    void regExpSlot(const QRegExp& val) { regExps << val; }
    void globalColorSlot(Qt::GlobalColor val) { globalColors << val; }

public:
    QList<int> ints;
    QList<uint> uints;
    QList<qlonglong> qlonglongs;
    QList<qulonglong> qulonglongs;
    QList<bool> bools;
    QList<double> doubles;
    //QList<const char*> chars; "const char*" is not a meta type
    QList<QByteArray> byteArrays;
    QList<QBitArray> bitArrays;
    QList<QString> strings;
    //QList<QLatin1String> latin1Strings; "QLatin1String" is not a meta type
    QList<QStringList> stringLists;
    QList<QChar> qchars;
    QList<QDate> dates;
    QList<QTime> times;
    QList<QDateTime> dateTimes;
    QList<QVariantList> lists;
    QList<QVariantMap> maps;
    QList<QSize> sizes;
    QList<QSizeF> sizeFs;
    QList<QPoint> points;
    QList<QPointF> pointFs;
    QList<QLine> lines;
    QList<QLineF> lineFs;
    QList<QRect> rects;
    QList<QRectF> rectFs;
    QList<QUrl> urls;
    QList<QLocale> locales;
    QList<QRegExp> regExps;
    QList<Qt::GlobalColor> globalColors;
};

#endif // RECEIVER_H
