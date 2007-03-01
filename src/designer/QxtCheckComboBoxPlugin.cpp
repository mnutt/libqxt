/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtCheckComboBox.h"
#include "QxtCheckComboBoxPlugin.h"
#include <QtPlugin>

QxtCheckComboBoxPlugin::QxtCheckComboBoxPlugin(QObject* parent) : QObject(parent)
{
}

QWidget* QxtCheckComboBoxPlugin::createWidget(QWidget* parent)
{
	return new QxtCheckComboBox(parent);
}

QString QxtCheckComboBoxPlugin::name() const
{
	return "QxtCheckComboBox";
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

QString QxtCheckComboBoxPlugin::includeFile() const
{
	return "QxtCheckComboBox";
}
