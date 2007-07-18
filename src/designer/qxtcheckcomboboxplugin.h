/****************************************************************************
**
** Copyright (C) J-P Nurmi <jpnurmi@gmail.com>. Some rights reserved.
**
** This file is part of the QxtGui module of the
** Qt eXTension library <http://libqxt.sourceforge.net>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef QXTCHECKCOMBOBOXPLUGIN_H
#define QXTCHECKCOMBOBOXPLUGIN_H

#include <QObject>
#include "qxtdesignerplugin.h"

class QxtCheckComboBoxPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtCheckComboBoxPlugin(QObject* parent = 0);
	
	QWidget* createWidget(QWidget* parent);
	QString domXml() const;
};

#endif // QXTCHECKCOMBOBOXPLUGIN_H
