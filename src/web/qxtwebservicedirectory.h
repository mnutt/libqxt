/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb  module of the Qxt library.
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
** <http://www.libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/

#ifndef QXTWEBSERVICEDIRECTORY_H
#define QXTWEBSERVICEDIRECTORY_H

#include <qxtabstractwebservice.h>
#include <qxtpimpl.h>
#include <QString>
class QxtAbstractWebSessionManager;
class QxtWebEvent;

class QxtWebServiceDirectoryPrivate;
class QxtWebServiceDirectory : public QxtAbstractWebService {
Q_OBJECT
public:
    QxtWebServiceDirectory(QxtAbstractWebSessionManager* sm, QObject* parent = 0);

    void addService(const QString& path, QxtAbstractWebService* service);
    void removeService(const QString& path);
    QxtAbstractWebService* service(const QString& path) const;

    virtual void pageRequestedEvent(QxtWebRequestEvent* event);
//     virtual void functionInvokedEvent(QxtWebRequestEvent* event);

    QString defaultRedirect() const;
    void setDefaultRedirect(const QString& path);

protected:
    virtual void unknownServiceRequested(QxtWebRequestEvent* event, const QString& name);
    virtual void indexRequested(QxtWebRequestEvent* event);

private:
    QXT_DECLARE_PRIVATE(QxtWebServiceDirectory);
};

#endif
