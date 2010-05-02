#include <QCoreApplication>
#include <QxtJSONRpcClient>
#include <QxtJSONRpcCall>
#include <QDebug>
#include <QStringList>
#include <QxtSignalWaiter>



int main(int argc, char ** argv){
    QCoreApplication app(argc,argv);

    if(app.arguments().count()<2){
        qDebug()<<"usage:  ./qxtjsonrpcclient method [arguments] \n  see http://www.raboof.com/projects/JayRock/Demo.ashx?help for methods to use";
        exit(1);
    }


    QxtJSONRpcClient client;
    client.setServiceUrl(QString("http://www.raboof.com/projects/JayRock/Demo.ashx"));



    QxtJSONRpcCall * call = client.call(app.arguments()[1],QVariant(app.arguments().mid(2)).toList());
    QxtSignalWaiter w(call,SIGNAL(finished()));
    w.wait();

    qDebug()<<call->result();
}

