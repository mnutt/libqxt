/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtNetwork module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/
#ifndef QXTPOP3COMMAND_P_H
#define QXTPOP3COMMAND_P_H

#include "qxtpop3reply.h"

#include <QTimer>

class QxtPop3ReplyPrivate;
class QxtPop3Private;
class QxtPop3ReplyImpl
{
public:
    QxtPop3ReplyImpl(QxtPop3ReplyPrivate& reply): m_reply(reply) {}
    virtual ~QxtPop3ReplyImpl() {}

    virtual QByteArray dialog(QByteArray received) = 0;

    static QByteArray buildCmd(QByteArray cmd, QByteArray arg)
    {
        return cmd + " " + arg + "\r\n";
    }

    static bool isAnswerOK(QByteArray line)
    {
        return line.indexOf("+OK") == 0;
    }

    static bool isAnswerERR(QByteArray line)
    {
        return line.indexOf("-ERR") == 0;
    }

protected:
    QxtPop3ReplyPrivate& m_reply;

};

class QxtPop3ReplyPrivate : public QObject, public QxtPrivate<QxtPop3Reply>
{
    Q_OBJECT
public:
    QxtPop3ReplyPrivate();
    virtual ~QxtPop3ReplyPrivate() {if (impl) delete impl;}

    QXT_DECLARE_PUBLIC(QxtPop3Reply)

    void finish(int code) {emit qxt_p().finished(code);}
    void progress(int pc) {emit qxt_p().progress(pc);}
    QTimer timer;

    virtual void run();
    QxtPop3ReplyImpl* impl;
    QxtPop3Reply::Status status;
    QxtPop3Reply::Type type;
    int timeout;
    QString errString;

public slots:
    void timedOut();
private:
    Q_DISABLE_COPY(QxtPop3ReplyPrivate)

};

class QxtPop3AuthReply: public QxtPop3Reply
{
    friend class QxtPop3Private;
private:
    QxtPop3AuthReply(QxtPop3Private* pop, int timeout, QObject* parent = 0);
    Q_DISABLE_COPY(QxtPop3AuthReply)
};

class QxtPop3DeleReply: public QxtPop3Reply
{
    friend class QxtPop3;
private:
    QxtPop3DeleReply(int which, int timeout, QObject* parent = 0);
};


class QxtPop3ResetReply: public QxtPop3Reply
{
    friend class QxtPop3;
private:
    QxtPop3ResetReply(int timeout, QObject* parent = 0);
};


class QxtPop3QuitReply: public QxtPop3Reply
{
    friend class QxtPop3;
private:
    QxtPop3QuitReply(int timeout, QObject* parent = 0);
};

#endif // QXTPOP3COMMAND_P_H
