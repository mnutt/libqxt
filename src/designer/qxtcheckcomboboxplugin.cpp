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
#include "qxtcheckcombobox.h"
#include "qxtcheckcomboboxplugin.h"
#include <QtPlugin>

QxtCheckComboBoxPlugin::QxtCheckComboBoxPlugin(QObject* parent)
	: QObject(parent), QxtDesignerPlugin("QxtCheckComboBox")
{
}

QWidget* QxtCheckComboBoxPlugin::createWidget(QWidget* parent)
{
	return new QxtCheckComboBox(parent);
}

QString QxtCheckComboBoxPlugin::domXml() const
{
	return "<widget class=\"QxtCheckComboBox\" name=\"qxtCheckComboBox\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>57</width>\n"
		"   <height>17</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}
