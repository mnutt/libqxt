/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qt eXTension library
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
#ifndef QXTITEMEDITORCREATOR_H
#define QXTITEMEDITORCREATOR_H

#include <QWidget>
#include <QItemEditorCreator>
#include "qxtglobal.h"
#include "qxtnamespace.h"

template <class T>
class QXT_GUI_EXPORT QxtItemEditorCreator : public QItemEditorCreator<T>
{
public:
    inline QxtItemEditorCreator(const QByteArray& valuePropertyName) : QItemEditorCreator<T>(valuePropertyName) { }

    inline QWidget* createWidget(QWidget* parent) const;

    QVariant defaultPropertyValue(const QByteArray& property) const { return properties.value(property); }
    void setDefaultPropertyValue(const QByteArray& property, const QVariant& value) { properties.insert(property, value); }

private:
    QHash<QByteArray, QVariant> properties;
};

template <class T>
QWidget* QxtItemEditorCreator<T>::createWidget(QWidget* parent) const
{
    QWidget* editor = QItemEditorCreator<T>::createWidget(parent);
    QHashIterator<QByteArray, QVariant> i(properties);
    while (i.hasNext())
    {
        i.next();
        editor->setProperty(i.key(), i.value());
    }
    return editor;
}

#endif // QXTITEMEDITORCREATOR_H
