/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
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

#ifndef QXTJOB_H
#define QXTJOB_H

#include <qxtpimpl.h>
#include <qxtglobal.h>

#include <QObject>

class QxtJobPrivate;
QT_BEGIN_NAMESPACE
class QThread;
QT_END_NAMESPACE

class QXT_CORE_EXPORT QxtJob : public QObject
{
Q_OBJECT
public:
    QxtJob();
    ~QxtJob();
    void exec(QThread * onthread);
    void join();
protected:
    virtual void run()=0; 
Q_SIGNALS:
    void done();
private:
    QXT_DECLARE_PRIVATE(QxtJob);
Q_SIGNALS:
    ///\priv
    void subseed();
};

#endif // QXTJOB_H
