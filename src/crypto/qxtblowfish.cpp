/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCrypto module of the Qxt library.
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

#include "qxtblowfish.h"
#ifdef HAVE_OPENSSL
#include <openssl/blowfish.h>
#endif // HAVE_OPENSSL

/*!
    \class QxtBlowfish QxtBlowfish
    \ingroup QxtCrypto
    \brief  Blowfish Encryption Class

    Usage:
    \code
    QxtBlowfish fish;
    fish.setPassword("foobar").

    QByteArray data("barblah");
    data = fish.encrypt(data);
    data = fish.decrypt(data);
    \endcode
*/

class QxtBlowfishPrivate : public QxtPrivate<QxtBlowfish>
{
public:
#ifdef HAVE_OPENSSL
    bf_key_st* key;
#endif // HAVE_OPENSSL
    QByteArray password;
};

QxtBlowfish::QxtBlowfish()
{
#ifdef HAVE_OPENSSL
    qxt_d().key = new BF_KEY;
#endif // HAVE_OPENSSL
}

QxtBlowfish::~QxtBlowfish()
{
#ifdef HAVE_OPENSSL
    delete qxt_d().key;
#endif // HAVE_OPENSSL
}

QByteArray QxtBlowfish::password() const
{
    return qxt_d().password;
}

void QxtBlowfish::setPassword(const QByteArray& password)
{
    qxt_d().password = password;
#ifdef HAVE_OPENSSL
    BF_set_key(qxt_d().key, password.size(), (uchar*)password.constData());
#endif // HAVE_OPENSSL
}

QByteArray QxtBlowfish::encrypt(const QByteArray& data) const
{
    QByteArray result;
#ifdef HAVE_OPENSSL
    result = data;
    int num = 0;
    uchar ivec[9];
    ivec[0] = (uchar)3887;
    ivec[1] = (uchar)3432;
    ivec[2] = (uchar)3887;
    ivec[3] = (uchar)2344;
    ivec[4] = (uchar)678;
    ivec[5] = (uchar)3887;
    ivec[6] = (uchar)575;
    ivec[7] = (uchar)2344;
    ivec[8] = (uchar)2222;

    BF_cfb64_encrypt(
        (const uchar*)data.constData(),
        (uchar*)result.data(),
        data.size(),
        qxt_d().key,
        ivec,
        &num,
        BF_ENCRYPT
    );

    result = result.toBase64();
#endif // HAVE_OPENSSL
    return result;
}

QByteArray QxtBlowfish::decrypt(const QByteArray& data) const
{
    QByteArray result;
#ifdef HAVE_OPENSSL
    QByteArray source = QByteArray::fromBase64(data);
    result = source;

    int num = 0;
    uchar ivec[9];
    ivec[0] = (uchar)3887;
    ivec[1] = (uchar)3432;
    ivec[2] = (uchar)3887;
    ivec[3] = (uchar)2344;
    ivec[4] = (uchar)678;
    ivec[5] = (uchar)3887;
    ivec[6] = (uchar)575;
    ivec[7] = (uchar)2344;
    ivec[8] = (uchar)2222;

    BF_cfb64_encrypt(
        (const uchar*)source.constData(),
        (uchar*)result.data(),
        source.size(),
        qxt_d().key,
        ivec,
        &num,
        BF_DECRYPT
    );
#endif // HAVE_OPENSSL
    return result;
}
