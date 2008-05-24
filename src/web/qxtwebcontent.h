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
** <http://www.libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/

#ifndef QXTWEBCONTENT_H
#define QXTWEBCONTENT_H

#include <QAbstractSocket>
#include <QByteArray>
#include <QHash>
#include <qxtpimpl.h>

class QxtWebContentPrivate;
class QxtWebContent : public QIODevice {
Q_OBJECT
public:
    QxtWebContent(int contentLength, const QByteArray& start, QIODevice* device);
    QxtWebContent(int contentLength, QIODevice* device);
    QxtWebContent(const QByteArray& content, QObject* parent = 0);
    static QHash<QString, QString> parseUrlEncodedQuery(const QString& data);

    virtual qint64 bytesAvailable() const;
    qint64 unreadBytes() const;

    void waitForAllContent();

public slots:
    void ignoreRemainingContent();

protected:
    virtual qint64 readData(char* data, qint64 maxSize);
    virtual qint64 writeData(const char* data, qint64 maxSize);

private slots:
    void errorReceived(QAbstractSocket::SocketError);

private:
    QXT_DECLARE_PRIVATE(QxtWebContent);
};

#endif
