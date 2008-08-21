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
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#ifndef QXTMAIL_H
#define QXTMAIL_H

#include <qxtpimpl.h>
#include <qxtglobal.h>
#include <qxtsharedprivate.h>

#include <QObject>
#include <QStringList>

struct QxtMailPrivate;
class QXT_WEB_EXPORT QxtMail
{
public:
    QxtMail();
    QxtMail(const QStringList& recipients,
                const QString& subject, const QString& body,
                const QStringList& extraHeaders = QStringList());

    QStringList recipients()    const;
    QString     sender()        const;
    QString     subject()       const;
    QString     body()          const;
    QStringList extraHeaders()  const;

    void setRecipients  (QStringList);
    void setSender      (QString);
    void setSubject     (QString);
    void setBody        (QString);
    void setExtraHeaders(QStringList);

    QString rfc822();

private:
    QxtSharedPrivate<QxtMailPrivate> qxt_d;
};

#endif // QXTMAIL_H
