/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb  module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtwebcore.h"
#include "qxtwebcore_p.h"

#include <QTimer>
#include <QUrl>
#include "qxtwebcontroller.h"
#include <QCoreApplication>
#include <QTcpSocket>
#include <QVariant>
#include <QtDebug>
#include <QUrl>
#include <ctime>

/*!
        \class QxtWebCore QxtWebCore
        \ingroup QxtWeb
        \brief qxtweb application core class. communicates, delegates, does all of the magic ;)


        QxtWebCore is the base class of your web application.
        it listens to the scgi protocoll

        construct one webcore object in the main function of your application.
        you must contruct it AFTER QCoreApplication and BEFORe any controllers.

        \code
        int main(int argc,char ** argv)
                {
                QCoreApplication  app(argc,argv);
                QxtWebCore core();
                core.listen(8080);
                QxtWebController controller("root");
                app.exec();
                }
        \endcode
*/

/*!
        \fn static QxtWebCore* instance();
        singleton accessor
        \fn static void send(QByteArray);
        Send data to the client. Use this rarely, but use it always when sending binary data such as images. \n
        normal text/html comunication should be done using the controllers echo() function \n
        note that after you called send the first time you cannot modify the header anymore \n
        sending may be ignored by the transport when there is no client currently handled
        \fn static QIODevice * socket();
        direct access to a iodevice for writing binary data. \n
        You shouldn't use that unless it's absolutly nessesary
        \fn static QxtError parseString(QByteArray str, post_t & POST);
        much like phps parse_string \n
        \fn static QByteArray readContent(int maxsize=5000);
        reads the content from the current socket if any has sent. \n
        returns an empty QByteArray on any error.  \n
        the content is cut at maxsize and not read from the socket.  \n
        FIXME:\warning: this function is BLOCKING.  while content is read from the client, no other requests can be handled.
        FIXME:\warning: due to paranoid timeouts this might not work for slow clients
 */















static QxtWebLegacyEngine * singleton_m=0;

//-----------------------interface----------------------------
QxtWebLegacyEngine::QxtWebLegacyEngine(QxtWebStatelessConnector * t):QObject()
{
    if (singleton_m)
        qFatal("you're trying to construct QxtWebCore twice!");
    singleton_m=this;
    sc=t;
    cc=0;
    connect(sc,SIGNAL(newConnection()),this,SLOT(incomming()));
}

QxtWebLegacyEngine::~QxtWebLegacyEngine()
{
    singleton_m=0;
}


void QxtWebLegacyEngine::send(QString a)
{
    Q_ASSERT(instance()->cc);
    instance()->cc->write(a.toUtf8());
}
void QxtWebLegacyEngine::header(QString a,QString b)
{
    Q_ASSERT(instance()->cc);
    instance()->cc->response().setValue(a,b);
}

QHttpRequestHeader &  QxtWebLegacyEngine::SERVER()
{
    Q_ASSERT(instance()->cc);
    return instance()->cc->request();
}

QIODevice * QxtWebLegacyEngine::socket()
{
    Q_ASSERT(instance()->cc);
    return instance()->cc;
}

void QxtWebLegacyEngine::redirect(QString l,int code)
{
     if(!instance()->cc)
        return;

    QByteArray loc =QUrl(l).toEncoded ();

    if (loc.isEmpty())
        loc="/";
    instance()->cc->response().setStatusLine(code);
    instance()->cc->response().setValue("location",loc);
    instance()->cc->write(QByteArray("<a href=\""+loc+"\">"+loc+"</a>"));

}

QxtWebLegacyEngine * QxtWebLegacyEngine::instance()
{
    if (!singleton_m)
        qFatal("no QxtWebCore constructed");
    return singleton_m;
}


void QxtWebLegacyEngine::close()
{
     if(!instance()->cc)
        return;
    instance()->cc->close();
    delete instance()->cc;
    instance()->cc=0;
}




void QxtWebLegacyEngine::incomming()
{


    Q_ASSERT_X(!cc,Q_FUNC_INFO,"inconsistent state");

    if(!sc->hasPendingConnections())
        sc->waitForNewConnection(-1);

    while(sc->hasPendingConnections ())
    {
        cc=sc->nextPendingConnection();
        cc->waitForReadyRead(10000);
        emit(request());

        ///--------------find controller ------------------
        QByteArray path="404";
        QStringList requestsplit = SERVER().path().split('/');
        if (requestsplit.count()>1)
        {
            path=requestsplit.at(1).toUtf8();
            if (path.trimmed().isEmpty())path="root";
        }
        else if (requestsplit.count()>0)
            path="root";

        ///--------------controller------------------

        QxtWebController * controller =qFindChild<QxtWebController *> (QCoreApplication::instance(), path );
        if (!controller)
        {
            QString e404=
            "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">"
            "<html><head>"
            "<title>404 Not Found</title>"
            "</head><body>"
            "<h1>Not Found</h1>"
            "<p>The requested Controller \""+path+"\" was not found on this server.</p>"
            "</body></html>";

            instance()->cc->response().setStatusLine ( 404, "Not Found");
            send(e404);
            close();
            qDebug("404 controller '%s' not found",path.constData());
            return;
        }

        int i=controller->invoke(cc);
        if (i!=0 && i!=2)
        {
            QString e404=
            "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">"
            "<html><head>"
            "<title>404 Not Found</title>"
            "</head><body>"
            "<h1>Not Found</h1>"
            "<p>The requested Path \""+SERVER().path()+"\" was not accepted by the Controller.</p>"
            "<p>If this was unexpected, check the error log or contact the website administrator.</p>"
            "</body></html>";

            instance()->cc->response().setStatusLine ( 404, "Not Found");
            send(e404);
            close();
            qDebug("DEFECT: path: '%s' return code: %i ",path.constData(),i);
            return;
        }
        if (i!=2) ///FIXME temporary solution for keepalive
            close();
    }
}



