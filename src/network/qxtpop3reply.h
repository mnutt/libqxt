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
#ifndef QXTPOP3REPLY_H
#define QXTPOP3REPLY_H


#include "qxtglobal.h"

#include <QObject>

class QxtPop3ReplyPrivate;
class QxtPop3ReplyImpl;
class QXT_NETWORK_EXPORT QxtPop3Reply: public QObject
{
    Q_OBJECT
    friend class QxtPop3;
    friend class QxtPop3Private;
public:

    enum Status {
        Pending,
        Running,
        Completed,
        Timedout,
        Error
    };

    enum ReturnCode {
        OK,
        Timeout,
        Failed,
        Aborted
    };

    enum Type {
        Auth,
        Quit,
        Stat,
        List,
        Reset,
        Dele,
        Retr,
        Top
    };

    struct MessageInfo
    {
        int id;
        int size;
    };

    Status status() const;
    QString error() const;
    Type type() const;

    virtual void cancel();

    virtual ~QxtPop3Reply();

Q_SIGNALS:
    void finished(int code);
    void progress(int percent);

protected:
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    QxtPop3Reply(int timeout, QObject* parent = 0);
//    void setError(const QString& s);
//    void setStatus(const Status);
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    void setup(Type type);
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    QxtPop3ReplyImpl* impl();
    /*!
      \internal
      This class isn't meant to be subclassed by client code. This API only exists for internal purposes.
      */
    const QxtPop3ReplyImpl* impl() const;

private:
    QByteArray dialog(QByteArray received);
    QXT_DECLARE_PRIVATE(QxtPop3Reply)
    Q_DISABLE_COPY(QxtPop3Reply)
};

#endif // QXTPOP3REPLY_H
