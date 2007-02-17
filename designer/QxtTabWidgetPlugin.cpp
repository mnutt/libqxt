/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTabWidget.h"
#include "QxtTabWidgetPlugin.h"
#include "QxtTabWidgetTaskMenu.h"
#include <QExtensionManager>
#include <QDesignerFormEditorInterface>

static const int DEFAULT_TAB_COUNT = 2;

QxtTabWidgetPlugin::QxtTabWidgetPlugin(QObject* parent) : QObject(parent)
{
}

QWidget* QxtTabWidgetPlugin::createWidget(QWidget* parent)
{
	QxtTabWidget* tabWidget = new QxtTabWidget(parent);
	for (int i = 0; i < DEFAULT_TAB_COUNT; ++i)
		tabWidget->addTab(new QWidget(tabWidget), tr("Tab %1").arg(tabWidget->count() + 1));
	return tabWidget;
}

QString QxtTabWidgetPlugin::name() const
{
	return "QxtTabWidget";
}

QString QxtTabWidgetPlugin::domXml() const
{
	return "<widget class=\"QxtTabWidget\" name=\"qxtTabWidget\" >"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>131</width>\n"
		"   <height>80</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>";
}

QString QxtTabWidgetPlugin::includeFile() const
{
	return "QxtTabWidget";
}

bool QxtTabWidgetPlugin::isContainer() const
{
	return true;
}

void QxtTabWidgetPlugin::initialize(QDesignerFormEditorInterface* editor)
{
	QxtDesignerPlugin::initialize(editor);
	
	QExtensionManager *manager = editor->extensionManager();
	Q_ASSERT(manager);
	manager->registerExtensions(new QxtTabWidgetTaskMenuFactory(manager),
				    Q_TYPEID(QDesignerTaskMenuExtension));
}
