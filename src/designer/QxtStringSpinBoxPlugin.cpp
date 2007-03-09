/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtStringSpinBox.h"
#include "QxtStringSpinBoxPlugin.h"
#include <QtDesigner>
#include <QtPlugin>

QxtStringSpinBoxPlugin::QxtStringSpinBoxPlugin(QObject* parent) : QObject(parent)
{
}

QWidget* QxtStringSpinBoxPlugin::createWidget(QWidget* parent)
{
	return new QxtStringSpinBox(parent);
}

QString QxtStringSpinBoxPlugin::name() const
{
	return "QxtStringSpinBox";
}

QString QxtStringSpinBoxPlugin::domXml() const
{
	return "<widget class=\"QxtStringSpinBox\" name=\"qxtStringSpinBox\" />";
}

QString QxtStringSpinBoxPlugin::includeFile() const
{
	return "QxtStringSpinBox";
}
