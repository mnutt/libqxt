/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtSpanSlider.h"
#include "QxtSpanSliderPlugin.h"
#include <QtPlugin>

QxtSpanSliderPlugin::QxtSpanSliderPlugin(QObject* parent) : QObject(parent)
{
}

QWidget* QxtSpanSliderPlugin::createWidget(QWidget* parent)
{
	return new QxtSpanSlider(parent);
}

QString QxtSpanSliderPlugin::name() const
{
	return "QxtSpanSlider";
}

QString QxtSpanSliderPlugin::domXml() const
{
	return "<widget class=\"QxtSpanSlider\" name=\"qxtSpanSlider\" />";
}

QString QxtSpanSliderPlugin::includeFile() const
{
	return "QxtSpanSlider";
}
