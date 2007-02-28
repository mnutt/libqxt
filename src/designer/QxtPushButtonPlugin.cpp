/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

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
