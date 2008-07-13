/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/

#include "qxtbasicfileloggerengine.h"
#include <QTime>

/*!
    \class QxtBasicFileLoggerEngine QxtBasicFileLoggerEngine
    \brief A basic file logger engine.
    \ingroup QxtCore

    \sa QxtLogger
 */

/*!
    Constructs a basic file logger engine with file name.
*/
QxtBasicFileLoggerEngine::QxtBasicFileLoggerEngine( const QString &fileName )
    : QxtAbstractFileLoggerEngine( fileName )
{
}

/*!
    \reimp
 */
void QxtBasicFileLoggerEngine::writeToFile(const QString &level, const QVariantList &messages)
{
    if ( messages.isEmpty() ) return;
    QString header = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] [" + level + "] ";
    QString padding;
    QIODevice* file = device();
    Q_ASSERT(file);
    file->write(header.toUtf8());
    for ( int i = 0; i < header.size(); i++ ) padding.append(" ");
    int count = 0;
    Q_FOREACH(QVariant out, messages )
    {
        if( !out.isNull() )
        {
            if ( count != 0 ) file->write(padding.toUtf8());
            file->write(out.toString().toUtf8()); 
            file->write("\n");
        }
        count++;
    }
}
