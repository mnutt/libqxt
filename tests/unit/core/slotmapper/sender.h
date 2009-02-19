#ifndef SENDER_H
#define SENDER_H

#include <QtCore> //krazy:exclude=qxtincludes

class Sender : public QObject
{
    Q_OBJECT
public:
    Sender() { }

signals:
    void intSignal(int val);
    void uintSignal(uint val);
    void qlonglongSignal(qlonglong val);
    void qulonglongSignal(qulonglong val);
    void boolSignal(bool val);
    void doubleSignal(double val);
    //void charSignal(const char* val); "const char*" is not a meta type
    void byteArraySignal(const QByteArray& val);
    void bitArraySignal(const QBitArray& val);
    void stringSignal(const QString& val);
    //void latin1StringSignal(const QLatin1String& val); "QLatin1String" is not a meta type
    void stringListSignal(const QStringList& val);
    void qcharSignal(const QChar& val);
    void dateSignal(const QDate& val);
    void timeSignal(const QTime& val);
    void dateTimeSignal(const QDateTime& val);
    void listSignal(const QVariantList& val);
    void mapSignal(const QVariantMap& val);
    void sizeSignal(const QSize& val);
    void sizeFSignal(const QSizeF& val);
    void pointSignal(const QPoint& val);
    void pointFSignal(const QPointF& val);
    void lineSignal(const QLine& val);
    void lineFSignal(const QLineF& val);
    void rectSignal(const QRect& val);
    void rectFSignal(const QRectF& val);
    void urlSignal(const QUrl& val);
    void localeSignal(const QLocale& val);
    void regExpSignal(const QRegExp& val);
    void globalColorSignal(Qt::GlobalColor val);

private:
    friend class tst_QxtSlotMapper;
};

#endif // SENDER_H
