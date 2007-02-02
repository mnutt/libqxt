/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTreeWidget.h"
#include "QxtTreeWidgetPlugin.h"
#include <QtPlugin>

#include <QDebug>
QxtTreeWidgetPlugin::QxtTreeWidgetPlugin(QObject* parent) : QObject(parent)
{
	qDebug() << "ctor";
}

QWidget* QxtTreeWidgetPlugin::createWidget(QWidget* parent)
{
	qDebug() << "createWidget";
	return new QxtTreeWidget(parent);
}

QString QxtTreeWidgetPlugin::name() const
{
	qDebug() << "name";
	return "QxtTreeWidget";
}

QString QxtTreeWidgetPlugin::domXml() const
{
	qDebug() << "xml";
	return "<widget class=\"QxtTreeWidget\" name=\"qxtTreeWidget\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>57</width>\n"
		"   <height>17</height>\n"
		"  </rect>\n"
		" </property>\n"
//		" <property name=\"text\" >\n"
//		"  <string>QxtTreeWidget</string>\n"
//		" </property>\n"
		"</widget>\n";
}

QString QxtTreeWidgetPlugin::includeFile() const
{
	qDebug() << "incl";
	return "QxtTreeWidget";
}
