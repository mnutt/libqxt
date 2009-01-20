#include <QtTest/QtTest>
#include <qxtslotmapper.h>

class tst_QxtSlotMapper : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qxtslotmapper_data();
    void qxtslotmapper();

    void addMapping_data();
    void addMapping();
    void connect_data();
    void connect();
    void qt_metacall_data();
    void qt_metacall();
    void removeMapping_data();
    void removeMapping();
};

// Subclass that exposes the protected functions.
class SubQxtSlotMapper : public QxtSlotMapper
{
public:};

// This will be called before the first test function is executed.
// It is only called once.
void tst_QxtSlotMapper::initTestCase()
{
}

// This will be called after the last test function is executed.
// It is only called once.
void tst_QxtSlotMapper::cleanupTestCase()
{
}

// This will be called before each test function is executed.
void tst_QxtSlotMapper::init()
{
}

// This will be called after every test function.
void tst_QxtSlotMapper::cleanup()
{
}

void tst_QxtSlotMapper::qxtslotmapper_data()
{
}

void tst_QxtSlotMapper::qxtslotmapper()
{
    SubQxtSlotMapper mapper;
#if 0
    mapper.addMapping(QVariant(), QObject*, char const*);
    QCOMPARE(mapper.connect(QObject const*, char const*), false);
    QCOMPARE(mapper.qt_metacall(QMetaObject::Call, -1, void**), -1);
    mapper.removeMapping(QVariant(), QObject*, char const*);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QVariant)
void tst_QxtSlotMapper::addMapping_data()
{
#if 0
    QTest::addColumn<QVariant>("parameter");
    QTest::addColumn<int>("receiverCount");
    QTest::addColumn<int>("memberCount");
    QTest::newRow("null") << QVariant() << 0 << 0;
#endif
}

// public void addMapping(QVariant const& parameter, QObject* receiver, char const* member)
void tst_QxtSlotMapper::addMapping()
{
#if 0
    QFETCH(QVariant, parameter);
    QFETCH(int, receiverCount);
    QFETCH(int, memberCount);

    SubQxtSlotMapper mapper;

    mapper.addMapping(parameter, receiver, member);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QxtSlotMapper::connect_data()
{
    QTest::addColumn<int>("senderCount");
    QTest::addColumn<int>("signalCount");
    QTest::addColumn<bool>("connect");
    QTest::newRow("null") << 0 << 0 << false;
}

// public bool connect(QObject const* sender, char const* signal)
void tst_QxtSlotMapper::connect()
{
#if 0
    QFETCH(int, senderCount);
    QFETCH(int, signalCount);
    QFETCH(bool, connect);

    SubQxtSlotMapper mapper;

    QCOMPARE(mapper.connect(sender, signal), connect);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QMetaObject::Call)
void tst_QxtSlotMapper::qt_metacall_data()
{
#if 0
    QTest::addColumn<QMetaObject::Call>("call");
    QTest::addColumn<int>("id");
    QTest::addColumn<int>("argumentsCount");
    QTest::addColumn<int>("qt_metacall");
    QTest::newRow("null") << QMetaObject::Call() << 0 << 0 << 0;
#endif
}

// public int qt_metacall(QMetaObject::Call call, int id, void** arguments)
void tst_QxtSlotMapper::qt_metacall()
{
#if 0
    QFETCH(QMetaObject::Call, call);
    QFETCH(int, id);
    QFETCH(int, argumentsCount);
    QFETCH(int, qt_metacall);

    SubQxtSlotMapper mapper;

    QCOMPARE(mapper.qt_metacall(call, id, arguments), qt_metacall);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QxtSlotMapper::removeMapping_data()
{
#if 0
    QTest::addColumn<QVariant>("parameter");
    QTest::addColumn<int>("receiverCount");
    QTest::addColumn<int>("memberCount");
    QTest::newRow("null") << QVariant() << 0 << 0;
#endif
}

// public void removeMapping(QVariant const& parameter, QObject* receiver = 0, char const* member = 0)
void tst_QxtSlotMapper::removeMapping()
{
#if 0
    QFETCH(QVariant, parameter);
    QFETCH(int, receiverCount);
    QFETCH(int, memberCount);

    SubQxtSlotMapper mapper;

    mapper.removeMapping(parameter, receiver, member);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

QTEST_MAIN(tst_QxtSlotMapper)
#include "tst_qxtslotmapper.moc"
