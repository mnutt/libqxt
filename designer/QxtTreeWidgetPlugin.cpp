/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTreeWidget.h"
#include "QxtTreeWidgetPlugin.h"
#include <QtPlugin>

QxtTreeWidgetPlugin::QxtTreeWidgetPlugin(QObject* parent) : QObject(parent)
{
}

QWidget* QxtTreeWidgetPlugin::createWidget(QWidget* parent)
{
	return new QxtTreeWidget(parent);
}

QString QxtTreeWidgetPlugin::name() const
{
	return "QxtTreeWidget";
}

QString QxtTreeWidgetPlugin::domXml() const
{
	return "<widget class=\"QxtTreeWidget\" name=\"qxtTreeWidget\" />";
}

QString QxtTreeWidgetPlugin::includeFile() const
{
	return "QxtTreeWidget";
}
