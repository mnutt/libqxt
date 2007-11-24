#include "qxtwebhttpconnector_p.h"

#include "qxtwebhttpconnector.h"


QxtWebHttpConnector::QxtWebHttpConnector(QObject * parent  ):QxtWebStatelessConnector(parent)
{
        connect(&qxt_d(),SIGNAL(newConnection()),this,SIGNAL(newConnection()));
}

bool QxtWebHttpConnector::start ( quint16 port, const QHostAddress & address)
{
    return qxt_d().listen(address,port);
}


QAbstractSocket::SocketError QxtWebHttpConnector::serverError () const
{
    return qxt_d().serverError();
}

QxtWebStatelessConnection * QxtWebHttpConnector::nextPendingConnection ()
{
    if(!hasPendingConnections())
        return 0;

    QxtWebHttpConnection * n= new QxtWebHttpConnection(qxt_d().nextPendingConnection(),this);
    return n;
}

bool QxtWebHttpConnector::hasPendingConnections () const
{
    return qxt_d().hasPendingConnections();

}

bool QxtWebHttpConnector::waitForNewConnection ( int msec , bool * timedOut  )
{
    return qxt_d().waitForNewConnection(msec,timedOut);
}





