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
#ifndef QXTPOP3COMMAND_H
#define QXTPOP3COMMAND_H


#include "qxtglobal.h"

#include <QObject>

class QxtPop3CommandPrivate;
class QXT_NETWORK_EXPORT QxtPop3Command: public QObject
{
    Q_OBJECT
    friend class QxtPop3;
    friend class QxtPop3Private;
public:

    enum Status {
        Pending,
        Running,
        Completed,
        Error
    };

    enum ReturnCode {
        OK,
        Timeout,
        Failed,
        Aborted
    };

    Status status() const;
    QString error() const;

    virtual void cancel();

Q_SIGNALS:
    void completed(int code);
    void progress(int percent);

protected:
    QxtPop3Command(int timeout, QObject* parent = 0);
    void setError(const QString& s);
    void setStatus(const Status);

    virtual QByteArray dialog(QByteArray received) = 0;

private:
    QXT_DECLARE_PRIVATE(QxtPop3Command)
    Q_DISABLE_COPY(QxtPop3Command)
};

#endif // QXTPOP3COMMAND_H
