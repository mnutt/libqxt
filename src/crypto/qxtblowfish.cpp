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
    \brief Blowfish encryption class

    Usage:
    \code
    QxtBlowfish fish;
    fish.setKey("foobar").

    QByteArray data("barblah");
    data = fish.encrypt(data);
    data = fish.decrypt(data);
    \endcode
*/

class QxtBlowfishPrivate : public QxtPrivate<QxtBlowfish>
{
public:
#ifdef HAVE_OPENSSL
    bf_key_st* bf_key;
#endif // HAVE_OPENSSL
    QByteArray key;
};

/*!
    Constructs a new QxtBlowfish with \a key.
 */
QxtBlowfish::QxtBlowfish(const QByteArray& key)
{
#ifdef HAVE_OPENSSL
    qxt_d().bf_key = new BF_KEY;
#endif // HAVE_OPENSSL
    if (!key.isNull())
        setKey(key);
}

/*!
    Destructs the QxtBlowfish instance.
 */
QxtBlowfish::~QxtBlowfish()
{
#ifdef HAVE_OPENSSL
    delete qxt_d().bf_key;
#endif // HAVE_OPENSSL
}

/*!
    Returns the key.
 */
QByteArray QxtBlowfish::key() const
{
    return qxt_d().key;
}

/*!
    Sets the \a key.
 */
void QxtBlowfish::setKey(const QByteArray& key)
{
    qxt_d().key = key;
#ifdef HAVE_OPENSSL
    BF_set_key(qxt_d().bf_key, key.size(), (uchar*)key.constData());
#endif // HAVE_OPENSSL
}

/*!
    Encrypts \a data.

    \sa setKey()
 */
QByteArray QxtBlowfish::encrypt(const QByteArray& data) const
{
    QByteArray result;
    Q_UNUSED(data);
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
        qxt_d().bf_key,
        ivec,
        &num,
        BF_ENCRYPT
    );

    result = result.toBase64();
#endif // HAVE_OPENSSL
    return result;
}

/*!
    Decrypts \a data.

    \sa setKey()
*/
QByteArray QxtBlowfish::decrypt(const QByteArray& data) const
{
    QByteArray result;
    Q_UNUSED(data);
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
        qxt_d().bf_key,
        ivec,
        &num,
        BF_DECRYPT
    );
#endif // HAVE_OPENSSL
    return result;
}

/*!
    This is an overloaded member function, provided for convenience. 
    This version can be invoked without first instantiating a QxtBlowfisn object. 

    Encrypts \a data with \a key.
 */
QByteArray QxtBlowfish::encrypted(const QByteArray& data, const QByteArray& key)
{
    return QxtBlowfish(key).encrypt(data);
}

/*!
    This is an overloaded member function, provided for convenience. 
    This version can be invoked without first instantiating a QxtBlowfisn object. 

    Decrypts \a data with \a key.
 */
QByteArray QxtBlowfish::decrypted(const QByteArray& data, const QByteArray& key)
{
    return QxtBlowfish(key).decrypt(data);
}
