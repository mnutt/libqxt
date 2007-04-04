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


#ifndef QXTCHECKCOMBOBOX_H
#define QXTCHECKCOMBOBOX_H

#include <QComboBox>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtPimpl.h>

class QxtCheckComboBoxPrivate;

class QXT_GUI_EXPORT QxtCheckComboBox : public QComboBox
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtCheckComboBox);
	Q_PROPERTY(QString separator READ separator WRITE setSeparator)
	Q_PROPERTY(QString defaultText READ defaultText WRITE setDefaultText)
	Q_PROPERTY(QStringList checkedItems READ checkedItems WRITE setCheckedItems)
	Q_PROPERTY(QxtCheckComboBox::CheckMode checkMode READ checkMode WRITE setCheckMode)
	Q_ENUMS(CheckMode)
	
public:
	enum CheckMode
	{
		CheckIndicator,
		CheckWholeItem
	};
	
	explicit QxtCheckComboBox(QWidget* parent = 0);
	virtual ~QxtCheckComboBox();
	
	QStringList checkedItems() const;
	void setCheckedItems(const QStringList& items);
	
	QString defaultText() const;
	void setDefaultText(const QString& text);
	
	Qt::CheckState itemCheckState(int index) const;
	void setItemCheckState(int index, Qt::CheckState state);
	
	QString separator() const;
	void setSeparator(const QString& separator);
	
	CheckMode checkMode() const;
	void setCheckMode(CheckMode mode);
	
signals:
	void checkedItemsChanged(const QStringList& items);

#ifndef QXT_DOXYGEN_RUN
protected:
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTCHECKCOMBOBOX_H
