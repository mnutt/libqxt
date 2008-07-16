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
#ifndef QxtStdin_H_GUARD
#define QxtStdin_H_GUARD
#include <qxtglobal.h>
#include <qxtpimpl.h>
#include <qxtpipe.h>


class QxtStdioPrivate;
class QXT_CORE_EXPORT QxtStdio : public QxtPipe
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtStdio);
public:
    /**constructs a QxtStdio with the given parent*/
    QxtStdio(QObject * parent=0);

    /**will block forever regardless of the parameter. returns false on EOF*/
    virtual bool waitForReadyRead ( int msecs );

    /**Blocks until EOF is received.*/
    void waitForEOF ();

protected:
    /**\reimp*/
    virtual qint64 writeData ( const char * data, qint64 maxSize );
    /**\reimp*/
    virtual void   receiveData (QByteArray data, const QxtPipe * sender );


};
#endif
