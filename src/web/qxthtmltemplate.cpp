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

/*!
        \class QxtHtmlTemplate QxtHtmlTemplate
        \ingroup web
        \brief Basic Html Template Engine

        open a file containing html code and php style variables.
        use the square bracket operators to assign content for a variable

        \code
        QxtHtmlTemplate index;
        if(!index.open)
                return 404;
        index["content"]="hello world";
        echo()<<index.render();
        \endcode
        the realatet html code would look like:
        \code
        <html>
        <head>
                <title>Test Page</title>
        </head>
                <?=content?>
        </html>
        \endcode
*/

/*!
        \fn QxtHtmlTemplate::open(const QString& filename)
        Returns true on sucess and false on failure.
        note that it will also return false for an empty html file.

        \fn QString QxtHtmlTemplate::render() const
        Uses the variables you set and renders the opened file.
        returns an empty string on failure.
        Does NOT take care of not assigned variables, they will remain in the returned string
 */

#include "qxthtmltemplate.h"
#include <QFile>

QxtHtmlTemplate::QxtHtmlTemplate() : QMap<QString,QString>()
{}


bool QxtHtmlTemplate::open(const QString& filename)
{
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    data = QString::fromLocal8Bit(f.readAll());
    f.close();
    if (data.isEmpty())
        return false;
    return true;
}

QString QxtHtmlTemplate::render() const
{
    QString output = data;
    foreach(QString key, keys())
    {
        output = output.replace("<?="+key+"?>", value(key));
    }
    return output;
}

