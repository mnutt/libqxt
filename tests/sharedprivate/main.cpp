/** ***** QxtMail test ***** */
#include <QTest>
#include <QSignalSpy>
#include <QxtMail>
#include <QDebug>
#include <QString>

int instances=0;


class MyPrivate;

class My
{
public:
    My();
    QString string() const;
    void setString(QString a);
private:
    QxtSharedPrivate<MyPrivate> d;
};


class MyPrivate
{
public:
    MyPrivate()
    {
        instances++;
    }
    ~MyPrivate()
    {
        instances--;
    }
    QString string() const 
    {
        return m_string;
    }

    void setString(QString a)
    {
        m_string=a;
    }

    QString m_string;
};


My::My()
{
    d=new MyPrivate;
}

QString My::string() const 
{
    return d().string();
}

void My::setString(QString a)
{
    return d().setString(a);
}



class QxtSharedPrivateTest : public QObject
{
Q_OBJECT
private slots:
    void sanity()
    {
        {
            QCOMPARE(instances,0);
            My m1;
            QCOMPARE(instances,1);
            My m2;
            QCOMPARE(instances,2);
        }
        QCOMPARE(instances,0);
    }
    void share()
    {
        My m1;
        QCOMPARE(instances,1);
        My m2(m1);
        QCOMPARE(instances,1);
    }
    void keepShareOnConstCall()
    {
        QCOMPARE(instances,0);
        My m1;
        QCOMPARE(instances,1);
        My m2(m1);
        QCOMPARE(instances,1);
        m1.string();
        QCOMPARE(instances,1);
    }
    void copyOnWrite()
    {
        QCOMPARE(instances,0);
        My m1;
        QCOMPARE(instances,1);
        My m2(m1);
        QCOMPARE(instances,1);
        m1.setString("bla");
        QCOMPARE(instances,2);
    }
    void implicitCopyCtor()
    {
        QCOMPARE(instances,0);
        My m1;
        m1.setString("bla");
        QCOMPARE(instances,1);

        My m2(m1);
        QCOMPARE(instances,1);

        QVERIFY(m1.string()=="bla");
        QCOMPARE(instances,1);
    }

};


int main(int argc, char ** argv)
{
    QCoreApplication app(argc,argv);
    QxtSharedPrivateTest test1;
    return QTest::qExec(&test1,argc,argv);
}


#include "main.moc"
