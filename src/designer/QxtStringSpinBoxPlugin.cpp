/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtStringSpinBox.h"
#include "QxtStringSpinBoxPlugin.h"
#include "QxtStringSpinBoxTaskMenu.h"
#include <QtDesigner>
#include <QtPlugin>

QxtStringSpinBoxPlugin::QxtStringSpinBoxPlugin(QObject* parent) : QObject(parent), init(false)
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
	return "<widget class=\"QxtStringSpinBox\" name=\"qxtStringSpinBox\">\n"
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

QString QxtStringSpinBoxPlugin::includeFile() const
{
	return "QxtStringSpinBox";
}

void QxtStringSpinBoxPlugin::initialize(QDesignerFormEditorInterface* formEditor)
{
	if (init) return;
	
	QExtensionManager* manager = formEditor->extensionManager();
	Q_ASSERT(manager != 0);
	
	manager->registerExtensions(new QxtStringSpinBoxTaskMenuFactory(manager),
				    Q_TYPEID(QDesignerTaskMenuExtension));
	
	init = true;
}
