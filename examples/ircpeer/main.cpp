#include "mainwindow.h"
#include <QApplication>


int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    MainWindow main;
    main.show();
    return app.exec();
}


#if 0
#include "qxtircpeer.h"
#include <QApplication>
#include <QTcpSocket>
#include <qxtsignalwaiter.h>
#include "ircwidget.h"
#include <QtDebug>

int main(int argc, char** argv) 
{
    if(argc < 3) qFatal() << "Usage: qxtirc NICK SERVER #CHANNEL";
    QApplication app(argc, argv);
    IrcWidget w("#qxt");
    w.show();
    QxtIRCPeer p;
    p.attachSlot("PRIVMSG", &w, SIGNAL(receiveMessage(QxtIRCName, QByteArray, QByteArray)));
    p.attachSignal(&w, SIGNAL(sendMessage(QxtIRCName, QByteArray, QByteArray)), "PRIVMSG");
    p.connect(QHostAddress("64.161.255.20"), 6667);
    QxtSignalWaiter::wait(&p, SIGNAL(peerConnected()));
    p.call("USER", QVariant(), QByteArray(app.arguments()[1]), QByteArray(app.arguments()[2]), QByteArray(app.arguments()[2]), QByteArray("QxtIRC User"));
    p.call("NICK", QVariant(), QByteArray(app.arguments()[1]));
    QxtSignalWaiter::wait(&p, SIGNAL(peerConnected()), 3000);
    p.call("JOIN", QVariant(), QByteArray(app.arguments()[3]));
    return app.exec();
}
#endif

