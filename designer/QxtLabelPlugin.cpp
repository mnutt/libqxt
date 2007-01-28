/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtLabel.h"
#include "QxtLabelPlugin.h"
#include <QtPlugin>

QxtLabelPlugin::QxtLabelPlugin(QObject* parent)
	: QObject(parent), initialized(false)
{
}

void QxtLabelPlugin::initialize(QDesignerFormEditorInterface* core)
{
	Q_UNUSED(core);
	if (initialized)
		return;
	initialized = true;
}

bool QxtLabelPlugin::isInitialized() const
{
	return initialized;
}

QWidget* QxtLabelPlugin::createWidget(QWidget* parent)
{
	return new QxtLabel(parent);
}

QString QxtLabelPlugin::name() const
{
	return "QxtLabel";
}

QString QxtLabelPlugin::group() const
{
	return "Display Widgets [Qxt]";
}

QIcon QxtLabelPlugin::icon() const
{
	return QIcon(":/logo.png");
}

QString QxtLabelPlugin::toolTip() const
{
	return "";
}

QString QxtLabelPlugin::whatsThis() const
{
	return "";
}

bool QxtLabelPlugin::isContainer() const
{
	return false;
}

QString QxtLabelPlugin::domXml() const
{
	return "<widget class=\"QxtLabel\" name=\"qxtLabel\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>57</width>\n"
		"   <height>17</height>\n"
		"  </rect>\n"
		" </property>\n"
		" <property name=\"text\" >\n"
		"  <string>QxtLabel</string>\n"
		" </property>\n"
		"</widget>\n";
}

QString QxtLabelPlugin::includeFile() const
{
	return "QxtLabel";
}

Q_EXPORT_PLUGIN2(qxtlabelplugin, QxtLabelPlugin)
