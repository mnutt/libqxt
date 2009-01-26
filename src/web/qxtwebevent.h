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

#ifndef QXTWEBEVENT_H
#define QXTWEBEVENT_H

#include <qxtglobal.h>
#include <QString>
#include <QByteArray>
#include <QStringList>
#include <QPointer>
#include <QUrl>
#include <QMultiHash>
#include <QDateTime>
QT_FORWARD_DECLARE_CLASS(QIODevice)
class QxtWebContent;

class QxtWebEvent
{
public:
    enum EventType
    {
        None = 0,
        Request,
        FileUpload,
        Page,
        StoreCookie,
        RemoveCookie,
        Redirect
    };

    QxtWebEvent(EventType type, int sessionID);
    virtual ~QxtWebEvent();

    inline EventType type() const
    {
        return m_type;
    }
    const int sessionID;

private:
    EventType m_type;
};

class QxtWebRequestEvent : public QxtWebEvent
{
public:
    QxtWebRequestEvent(int sessionID, int requestID, const QUrl& url);
    ~QxtWebRequestEvent();

    const int requestID;

    QUrl url;
    const QUrl originalUrl;
    QString contentType;
    QPointer<QxtWebContent> content;
    QString method;
    QString remoteAddress;

    QMultiHash<QString, QString> cookies;
    QMultiHash<QString, QString> headers;
};

/* TODO: refactor and implement
class QxtWebFileUploadEvent : public QxtWebEvent {
public:
    QxtWebFileUploadEvent(int sessionID);

    QString filename;
    int contentLength;
    QIODevice* content;
};
*/

class QxtWebRedirectEvent;
class QxtWebPageEvent : public QxtWebEvent
{
public:
    QxtWebPageEvent(int sessionID, int requestID, QIODevice* source = 0);
    QxtWebPageEvent(int sessionID, int requestID, QByteArray source);    // creates a QBuffer
    virtual ~QxtWebPageEvent();

    QPointer<QIODevice> dataSource;          // data is read from this device and written to the client
    bool chunked, streaming;

    const int requestID;
    int status;
    QByteArray statusMessage, contentType;

private:
    friend class QxtWebRedirectEvent;
    QxtWebPageEvent(QxtWebEvent::EventType typeOverride, int sessionID, int requestID, QByteArray source);
};

class QxtWebErrorEvent : public QxtWebPageEvent
{
public:
    QxtWebErrorEvent(int sessionID, int requestID, int status, QByteArray statusMessage);
};

class QxtWebStoreCookieEvent : public QxtWebEvent
{
public:
    QxtWebStoreCookieEvent(int sessionID, QString name, QString data, QDateTime expiration = QDateTime());

    QString name;
    QString data;
    QDateTime expiration;
};

class QxtWebRemoveCookieEvent : public QxtWebEvent
{
public:
    QxtWebRemoveCookieEvent(int sessionID, QString name);

    QString name;
};

class QxtWebRedirectEvent : public QxtWebPageEvent
{
public:
    QxtWebRedirectEvent(int sessionID, int requestID, const QString& destination, int statusCode = 302);

    QString destination;
};

#endif // QXTWEBEVENT_H
