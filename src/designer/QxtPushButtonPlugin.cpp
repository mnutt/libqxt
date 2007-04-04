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


#include "QxtPushButton.h"
#include "QxtPushButtonPlugin.h"
#include <QtPlugin>

QxtPushButtonPlugin::QxtPushButtonPlugin(QObject* parent) : QObject(parent)
{
}
QWidget* QxtPushButtonPlugin::createWidget(QWidget* parent)
{
	return new QxtPushButton(parent);
}

QString QxtPushButtonPlugin::name() const
{
	return "QxtPushButton";
}
QString QxtPushButtonPlugin::domXml() const
{
	return "<widget class=\"QxtPushButton\" name=\"qxtPushButton\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>105</width>\n"
		"   <height>27</height>\n"
		"  </rect>\n"
		" </property>\n"
		" <property name=\"text\" >\n"
		"  <string>QxtPushButton</string>\n"
		" </property>\n"
		"</widget>\n";
}

QString QxtPushButtonPlugin::includeFile() const
{
	return "QxtPushButton";
}
