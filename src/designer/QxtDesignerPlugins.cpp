/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtDesignerPlugins.h"
#include "QxtLabelPlugin.h"
#include "QxtPushButtonPlugin.h"
#include "QxtTreeWidgetPlugin.h"
#include "QxtCheckComboBoxPlugin.h"
#include "QxtStringSpinBoxPlugin.h"
#include <QtPlugin>

QList<QDesignerCustomWidgetInterface*> QxtDesignerPlugins::customWidgets() const
{
	QList<QDesignerCustomWidgetInterface*> plugins;
	plugins << new QxtLabelPlugin()
		<< new QxtPushButtonPlugin()
		<< new QxtCheckComboBoxPlugin()
		<< new QxtStringSpinBoxPlugin()
		<< new QxtTreeWidgetPlugin();
	return plugins;
}

Q_EXPORT_PLUGIN(QxtDesignerPlugins)
