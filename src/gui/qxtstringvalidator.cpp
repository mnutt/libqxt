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

#include "qxtstringvalidator.h"
#include "qxtstringvalidator_p.h"

#include <QRegExp>
#include <QDebug>

/*!
    \class QxtStringValidator QxtStringValidator
    \ingroup gui
    \brief The QxtStringValidator class provides validation on a QStringList

    The QxtStringValidator class provides validation on a QStringList.
    It is searching a QStringList for occurence of the QString input.
    For a partial match it returns QValidator::Intermediate and for a full match QValidator::Acceptable.
   
   Example usage:
    \code

    QLineEdit * testLineEdit = new QLineEdit();

    QStringList testList;
    testList << "StringTestString" << "sTrInGCaSe"<< "StringTest"<< "String"<< "Foobar"<< "BarFoo"<< "QxtLib";

    QxtStringValidator *validator = new QxtStringValidator(ui.lineEdit, testList);
    //change lookup case sensitivity
    validator->setCaseSensitivity(Qt::CaseInsensitive);

    testLineEdit->setValidator(validator);

    \endcode
 */

/*!
    Constructs a validator object with a parent object that accepts any string in the stringlist. 
*/
QxtStringValidator::QxtStringValidator(QObject * parent, const QStringList &stringList ) : QValidator(parent)
{
    QXT_INIT_PRIVATE(QxtStringValidator);
    qxt_d().data = stringList;
}

QxtStringValidator::~QxtStringValidator(void)
{
}

/*!
    Fixes up the string input if there is no exact match in the stringlist.
    The first match in the stringlist is used to fix the input.
*/
void QxtStringValidator::fixup ( QString & input ) const
{
    qDebug()<<"Fixup called";

    if(qxt_d().data.contains(input,qxt_d().cs))
        return;

    QRegExp match(QString("^%1.*").arg(input));
    match.setCaseSensitivity(qxt_d().cs);
    int iPossibleStringIndex = qxt_d().data.indexOf(match);

    if(iPossibleStringIndex >= 0)
        input = qxt_d().data[iPossibleStringIndex];

}

/*!
    uses stringlist as new validation list
*/
void QxtStringValidator::setStringList(QStringList &stringList)
{
    qxt_d().data = stringList;
}

/*!
    Returns Acceptable if the string input matches a item in the stringlist.
    Returns Intermediate if the string input matches a item in the stringlist partial.
    Returns Invalid otherwise.

    Note: A partial match means the beginning of the strings are matching:
        qxtL matches qxtLib but not testqxtLib
*/
QValidator::State QxtStringValidator::validate ( QString & input, int & pos ) const
{
    Q_UNUSED(pos);

    if(qxt_d().data.contains(input,qxt_d().cs))
    {
        qDebug()<<input<<" is QValidator::Acceptable";
        return QValidator::Acceptable;
    }

    QRegExp match(QString("^%1.*").arg(input));
    match.setCaseSensitivity(qxt_d().cs);

    if(qxt_d().data.indexOf(match) >= 0)
    {
     qDebug()<<input<<" is QValidator::Intermediate";
     return QValidator::Intermediate;
    }

    qDebug()<<input<<" is QValidator::Invalid";
    return QValidator::Invalid;
}

/*!
    Returns Qt::CaseSensitive if the QxtStringValidator is matched case sensitively; otherwise returns Qt::CaseInsensitive. 
    \sa setCaseSensitivity().
*/
Qt::CaseSensitivity QxtStringValidator::caseSensitivity () const
{
    return qxt_d().cs;
}

/*!
    Sets case sensitive matching to cs. 
    If cs is Qt::CaseSensitive, inp matches input but not INPUT. 
    \sa caseSensitivity().
*/
void QxtStringValidator::setCaseSensitivity ( Qt::CaseSensitivity caseSensitivity )
{
    qxt_d().cs = caseSensitivity;
}
