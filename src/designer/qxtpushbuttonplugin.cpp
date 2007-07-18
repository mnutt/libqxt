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
#include "qxtpushbutton.h"
#include "qxtpushbuttonplugin.h"
#include <QtPlugin>

QxtPushButtonPlugin::QxtPushButtonPlugin(QObject* parent)
	: QObject(parent), QxtDesignerPlugin("QxtPushButton")
{
}
QWidget* QxtPushButtonPlugin::createWidget(QWidget* parent)
{
	return new QxtPushButton(parent);
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
