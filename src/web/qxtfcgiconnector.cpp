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
#include "qxtfcgiconnector.h"
#include "qxtfcgiconnector_p.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QTextStream>
#include "qxtstdstreambufdevice.h"
#include "qxtsignalwaiter.h"


QxtFcgiConnector::QxtFcgiConnector():QxtAbstractWebConnector()
        {
        qRegisterMetaType<server_t>("server_t");
        qRegisterMetaTypeStreamOperators<server_t>("server_t");
        QXT_INIT_PRIVATE(QxtFcgiConnector);
        }

int QxtFcgiConnector::start (quint16 ,const QHostAddress & )
        {
        qxt_d().start();
        return QxtSignalWaiter::wait(&qxt_d(),SIGNAL(started()),20000);

        }

QIODevice * QxtFcgiConnector::socket()
        {
        return qxt_d().io;
        }


QByteArray QxtFcgiConnector::content(quint64 maxsize)
        {
        QByteArray a= qxt_d().io->read(maxsize);
        qxt_d().io->readAll();  //apache handler bug
        return a;

        }


void QxtFcgiConnector::sendHeader(server_t & answer)
                {
                if(!answer.contains("Status"))
                        answer["Status"]="200 OK";
                if(!answer.contains("Content-Type"))
                        answer["Content-Type"]="text/html; charset=utf-8";

                server_t::const_iterator i = answer.constBegin();
                while (i != answer.constEnd()) 
                        {
                        qxt_d().io->write(i.key()+": "+i.value()+"\r\n");
                        ++i;
                        }
                qxt_d().io->write("\r\n");
                }

void  QxtFcgiConnector::close()
        {
        emit(aboutToClose());
        qxt_d().open=false;
        emit(qxt_d().close_ss());
        }


/* ********** IMPL ***********/


QxtFcgiConnectorPrivate::QxtFcgiConnectorPrivate()
        {
        open=false;
        io=0;
        qRegisterMetaType<server_t>("server_t");
        qRegisterMetaTypeStreamOperators<server_t>("server_t");
        }

void QxtFcgiConnectorPrivate::run()
        {
        qRegisterMetaType<server_t>("server_t");
        qRegisterMetaTypeStreamOperators<server_t>("server_t");

        FCGX_Request request;
        FCGX_Init();
        FCGX_InitRequest(&request, 0, 0);

        ///FIXME: i just need a damn fd to use select() on. arrg
        while (FCGX_Accept_r(&request) == 0)
                {
                open=true;
                fcgi_streambuf   fio_in(request.in);
                fcgi_streambuf   fio_out(request.out);

                io= new QxtStdStreambufDevice (&fio_in,&fio_out);

                server_t SERVER;
                const char * const * envp=request.envp;
                for ( ; *envp; ++envp)
                        {
                        QByteArray ee(*envp);
                        SERVER[ee.left(ee.indexOf('='))]=ee.mid(ee.indexOf('=')+1);
                        }



                /*
                QTextStream(io)  << "Content-type: text/html\r\n\r\n<H4>Request Environment</H4>\n<PRE>\n<H4>Standard Input - "<<clen;
                if (clen == STDIN_MAX) 
                        QTextStream(io)  << " (STDIN_MAX)";
                QTextStream(io)  << " bytes</H4>\n";
                if (clen)
                        io->write(content, clen);
                */


                emit(qxt_p().incomming(SERVER));
                /// heck this is a frikin waste of RAM, cpu and my nerves.
                /// I hope those arrogants retards burn in hell for it.
                if(open)
                        QxtSignalWaiter::wait(this,SIGNAL(close_ss()));
                open=false;
                delete(io);io=0;

                }
        }










