#include <QCoreApplication>
#include <QxtWebCore>
#include <QxtWebHttpConnector>
#include "hello.h"

int main(int argc, char ** argv)
{
    QCoreApplication app(argc,argv);
    QxtWebHttpConnector http;
    QxtWebLegacyEngine core(&http);
    HelloWorld root;
    if(!http.start(80))
    {
        qFatal("got root?");
    }
    qDebug("great. now point your browser to http://localhost");
    app.exec();
}


