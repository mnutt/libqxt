/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/

#ifndef __QXTSTRINGLISTVALIDATOR_H__
#define __QXTSTRINGLISTVALIDATOR_H__

#include <QValidator>
#include <QStringList>
#include "qxtpimpl.h"
#include "qxtglobal.h"

class QxtStringValidatorPrivate;

class QXT_GUI_EXPORT QxtStringValidator : public QValidator
{
    Q_OBJECT

    public:
        QxtStringValidator (QObject * parent, const QStringList &stringList = QStringList()); 
        ~QxtStringValidator ();
        
        virtual void fixup ( QString & input ) const;
        virtual QValidator::State validate ( QString & input, int & pos ) const;

        Qt::CaseSensitivity caseSensitivity () const;
        void setCaseSensitivity ( Qt::CaseSensitivity caseSensitivity );

        void setStringList(QStringList &stringList);

    private:
        QXT_DECLARE_PRIVATE(QxtStringValidator);
};

#endif //__QXTSTRINGLISTVALIDATOR_H__
