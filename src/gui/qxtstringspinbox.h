/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/


#ifndef QXTSTRINGSPINBOX_H
#define QXTSTRINGSPINBOX_H

#include <QSpinBox>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtStringSpinBoxPrivate;

class QXT_GUI_EXPORT QxtStringSpinBox : public QSpinBox
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtStringSpinBox);
	Q_PROPERTY(QStringList strings READ strings WRITE setStrings)
	
public:
	explicit QxtStringSpinBox(QWidget* pParent = 0);
	virtual ~QxtStringSpinBox();
	
	const QStringList& strings() const;
	void setStrings(const QStringList& strings);
	
#ifndef QXT_DOXYGEN_RUN
	virtual void fixup(QString& input) const;
	virtual QValidator::State validate(QString& input, int& pos) const;

protected:
	virtual QString textFromValue(int value) const;
	virtual int valueFromText(const QString& text) const;
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTSTRINGSPINBOX_H
