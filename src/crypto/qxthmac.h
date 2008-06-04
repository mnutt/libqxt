/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCrypto module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/

#ifndef QXTHMAC_H
#define QXTHMAC_H

#if QT_VERSION > 0x040300
#   warning QxtHmac requires Qt 4.3.0 or greater
#else

#include <QCryptographicHash>
#include "qxtpimpl.h"

class QxtHmacPrivate;
class QxtHmac {
public:
    typedef QCryptographicHash::Algorithm Algorithm;

    QxtHmac(QCryptographicHash::Algorithm algorithm);

    void setKey(QByteArray key);
    void reset();
    
    void addData(const char* data, int length);
    void addData(const QByteArray& data);
    
    QByteArray innerHash() const;
    QByteArray result();
    bool verify(const QByteArray& otherInner);

    static QByteArray hash(const QByteArray& key, const QByteArray& data, Algorithm algorithm);
    static bool verify(const QByteArray& key, const QByteArray& hmac, const QByteArray& inner, Algorithm algorithm);

private:
    QXT_DECLARE_PRIVATE(QxtHmac)
};

#endif
#endif
