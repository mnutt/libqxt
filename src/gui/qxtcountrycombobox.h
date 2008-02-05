/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtDesigner module of the Qt eXTension library
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

#ifndef QXTCOUNTRYCOMBOBOX_H
#define QXTCOUNTRYCOMBOBOX_H

#include <QComboBox>
#include <QLocale>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtCountryComboBoxPrivate;

class QXT_GUI_EXPORT QxtCountryComboBox : public QComboBox
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtCountryComboBox);
    Q_PROPERTY(QString currentCountryName READ currentCountryName)
#if QT_VERSION >= 0x040300
    Q_PROPERTY(QLocale::Country currentCountry READ currentCountry WRITE setCurrentCountry)
#endif

public:
    explicit QxtCountryComboBox(QWidget* parent = 0);
    virtual ~QxtCountryComboBox();

    QLocale::Country currentCountry() const;
    QString currentCountryName() const;

public slots:
    void setCurrentCountry(QLocale::Country country);

signals:
    void currentCountryChanged(QLocale::Country country);
    void currentCountryNameChanged(const QString& name);

#ifdef QXT_DESIGNER_MODE
protected:
    void paintEvent(QPaintEvent *e);
#endif
};



#endif  //QXTCOUNTRYCOMBOBOX_H
