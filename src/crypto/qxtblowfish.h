/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtCrypto module of the Qxt library.
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

#ifndef QXTBLOWFISH_H
#define QXTBLOWFISH_H

#include <qxtpimpl.h>
#include <qxtglobal.h>
#include <QByteArray>
class QxtBlowfishPrivate;

class QXT_CRYPTO_EXPORT QxtBlowfish
{
    QXT_DECLARE_PRIVATE(QxtBlowfish);

public:
    QxtBlowfish(const QByteArray& key = QByteArray());
    ~QxtBlowfish();

    QByteArray key() const;
    void setKey(const QByteArray& key);

    QByteArray encrypt(const QByteArray& data) const;
    QByteArray decrypt(const QByteArray& data) const;

    static QByteArray encrypted(const QByteArray& data, const QByteArray& key);
    static QByteArray decrypted(const QByteArray& data, const QByteArray& key);
};

#endif // QXTBLOWFISH_H
