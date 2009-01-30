#include <QCoreApplication>
#include <QxtWebScgiConnector>
#include <QDebug>
#include <QTimer>
#include <QTextStream>



int main (int argc,char ** argv)
{
    QCoreApplication app(argc,argv);

    QxtWebScgiConnector c;
    qDebug()<<"start:"<<c.start ( 8900, QHostAddress::LocalHost );

    forever
    {
        qDebug()<<"waitForNewConnection:"<<c.waitForNewConnection(-1);
        QxtWebStatelessConnection * st=c.nextPendingConnection();
        qDebug()<<"waitForReadyRead:"<<st->waitForReadyRead(10000);



        QTextStream stream(st);
        stream<<"<h1>HI!</h1>";

        stream<<"You requested: "<<st->request().path()<<"<br/>";
        stream<<"And sent me: "<<st->readAll()<<"<br/>";
        stream<<"<form action=\"/\" method=\"post\"><input type=\"text\" name=\"text\" /></form>";
        stream.flush();
        delete (st);
    }
}




