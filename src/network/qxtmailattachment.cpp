/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtWeb module of the Qxt library.
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

/*!
 * \class QxtMailAttachment
 * \inmodule QxtNetwork
 * \brief The QxtMailAttachment class represents an attachement to a QxtMailMessage
 */




#include "qxtmailattachment.h"
#include "qxtmail_p.h"
#include <QTextCodec>
#include <QBuffer>
#include <QPointer>
#include <QFile>
#include <QtDebug>

class QxtMailAttachmentPrivate : public QSharedData
{
public:
    QHash<QString, QString> extraHeaders;
    QString contentType;
    // those two members are mutable because they may change in the const rawData() method of QxtMailAttachment,
    // while caching the raw data for the attachment if needed.
    mutable QPointer<QIODevice> content;
    mutable bool deleteContent;

    QxtMailAttachmentPrivate()
    {
        content = 0;
        deleteContent = false;
        contentType = "text/plain";
    }

    ~QxtMailAttachmentPrivate()
    {
        if (deleteContent && content)
            content->deleteLater();
        deleteContent = false;
        content = 0;
    }
};

QxtMailAttachment::QxtMailAttachment()
{
    qxt_d = new QxtMailAttachmentPrivate;
}

QxtMailAttachment::QxtMailAttachment(const QxtMailAttachment& other) : qxt_d(other.qxt_d)
{
    // trivial copy constructor
}

QxtMailAttachment::QxtMailAttachment(const QByteArray& content, const QString& contentType)
{
    qxt_d = new QxtMailAttachmentPrivate;
    setContentType(contentType);
    setContent(content);
}

QxtMailAttachment::QxtMailAttachment(QIODevice* content, const QString& contentType)
{
    qxt_d = new QxtMailAttachmentPrivate;
    setContentType(contentType);
    setContent(content);
}

QxtMailAttachment& QxtMailAttachment::operator=(const QxtMailAttachment & other)
{
    qxt_d = other.qxt_d;
    return *this;
}

QxtMailAttachment::~QxtMailAttachment()
{
    // trivial destructor
}

QIODevice* QxtMailAttachment::content() const
{
    return qxt_d->content;
}

void QxtMailAttachment::setContent(const QByteArray& content)
{
    if (qxt_d->deleteContent && qxt_d->content)
        qxt_d->content->deleteLater();
    qxt_d->content = new QBuffer;
    setDeleteContent(true);
    static_cast<QBuffer*>(qxt_d->content.data())->setData(content);
}

void QxtMailAttachment::setContent(QIODevice* content)
{
    if (qxt_d->deleteContent && qxt_d->content)
        qxt_d->content->deleteLater();
    qxt_d->content = content;
}

bool QxtMailAttachment::deleteContent() const
{
    return qxt_d->deleteContent;
}

void QxtMailAttachment::setDeleteContent(bool enable)
{
    qxt_d->deleteContent = enable;
}

QString QxtMailAttachment::contentType() const
{
    return qxt_d->contentType;
}

void QxtMailAttachment::setContentType(const QString& contentType)
{
    qxt_d->contentType = contentType;
}

QHash<QString, QString> QxtMailAttachment::extraHeaders() const
{
    return qxt_d->extraHeaders;
}

QString QxtMailAttachment::extraHeader(const QString& key) const
{
    return qxt_d->extraHeaders[key.toLower()];
}

bool QxtMailAttachment::hasExtraHeader(const QString& key) const
{
    return qxt_d->extraHeaders.contains(key.toLower());
}

void QxtMailAttachment::setExtraHeader(const QString& key, const QString& value)
{
    qxt_d->extraHeaders[key.toLower()] = value;
}

void QxtMailAttachment::setExtraHeaders(const QHash<QString, QString>& a)
{
    QHash<QString, QString>& headers = qxt_d->extraHeaders;
    headers.clear();
    foreach(const QString& key, a.keys())
    {
        headers[key.toLower()] = a[key];
    }
}

void QxtMailAttachment::removeExtraHeader(const QString& key)
{
    qxt_d->extraHeaders.remove(key.toLower());
}

QByteArray QxtMailAttachment::mimeData()
{
    QTextCodec* latin1 = QTextCodec::codecForName("latin1");
    QByteArray rv = "Content-Type: " + qxt_d->contentType.toAscii() + "\r\nContent-Transfer-Encoding: base64\r\n";
    foreach(const QString& r, qxt_d->extraHeaders.keys())
    {
        rv += qxt_fold_mime_header(r.toAscii(), extraHeader(r), latin1);
    }
    rv += "\r\n";

    const QByteArray& d = rawData();
    for (int pos = 0; pos < d.length(); pos += 57)
    {
        rv += d.mid(pos, 57).toBase64() + "\r\n";
    }
    return rv;
}

const QByteArray& QxtMailAttachment::rawData() const
{
    if (qxt_d->content == 0)
    {
        qWarning("QxtMailAttachment::rawData(): Content not set!");
        static QByteArray defaultRv;
        return defaultRv;
    }
    if (qobject_cast<QBuffer *>(qxt_d->content.data()) == 0)
    {
        // content isn't hold in a buffer but in another kind of QIODevice
        // (probably a QFile...). Read the data and cache it into a buffer
        static QByteArray empty;
        QIODevice* c = content();
        if (!c->isOpen() && !c->open(QIODevice::ReadOnly))
        {
            qWarning() << "QxtMailAttachment::rawData(): Cannot open content for reading";
            return empty;
        }
        QBuffer* cache = new QBuffer();
        cache->open(QIODevice::WriteOnly);
        char buf[1024];
        while (!c->atEnd())
        {
            cache->write(buf, c->read(buf, 1024));
        }
        if (qxt_d->deleteContent && qxt_d->content)
        qxt_d->content->deleteLater();
        qxt_d->content = cache;
        qxt_d->deleteContent = true;
    }
    return qobject_cast<QBuffer *>(qxt_d->content.data())->data();
}


// gives only a hint, based on content-type value.
// return true if the content-type corresponds to textual data (text/*, application/xml...)
// and false if unsure, so don't interpret a 'false' response as 'it's binary data...
bool QxtMailAttachment::isText() const
{
    return isTextMedia(contentType());
}

QxtMailAttachment QxtMailAttachment::fromFile(const QString& filename)
{
    QxtMailAttachment rv(new QFile(filename));
    rv.setDeleteContent(true);
    return rv;
}
