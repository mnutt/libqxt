#include <QTest>
#include <QSignalSpy>
#include <QxtSharedPrivate>
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









class My2Private;

class My2
{
public:
    My2();
    QString string() const;
    void setString(QString a);
    void couseDetach();
private:
    QxtSharedPrivate<My2Private> d;
};


class My2Private
{
public:
    My2Private()
    {
        instances++;
    }
    virtual ~My2Private()
    {
        instances--;
    }

    My2Private(const My2Private & )
    {
        instances++;
        m_string="foo";
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

    void couseDetach()
    {
        //nothing. but it's not const
    }
};


My2::My2()
{
    d=new My2Private;
}

QString My2::string() const 
{
    return d().string();
}

void My2::setString(QString a)
{
    d().setString(a);
}
void My2::couseDetach()
{
    d().couseDetach();
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
        My2 m1;
        QCOMPARE(instances,1);
        My2 m2(m1);
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
    void explicitCopyCtor()
    {
        QCOMPARE(instances,0);
        My2 m1;
        m1.setString("bla");
        QCOMPARE(instances,1);

        My2 m2(m1);
        QCOMPARE(instances,1);

        m2.couseDetach();
        QVERIFY(m2.string()=="foo");
        QCOMPARE(instances,2);
    }
};


int main(int argc, char ** argv)
{
    QCoreApplication app(argc,argv);
    QxtSharedPrivateTest test1;
    return QTest::qExec(&test1,argc,argv);
}


#include "main.moc"
