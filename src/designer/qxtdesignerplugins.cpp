/****************************************************************************
**
** Copyright (C) J-P Nurmi <jpnurmi@gmail.com>. Some rights reserved.
**
** This file is part of the QxtGui module of the
** Qt eXTension library <http://libqxt.sourceforge.net>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "qxtdesignerplugins.h"
#include "qxtcheckcomboboxplugin.h"
#include "qxtgroupboxplugin.h"
#include "qxtlabelplugin.h"
#include "qxtlistwidgetplugin.h"
#include "qxtprogresslabelplugin.h"
#include "qxtpushbuttonplugin.h"
#include "qxtspansliderplugin.h"
#include "qxtstarsplugin.h"
#include "qxtstringspinboxplugin.h"
#include "qxttablewidgetplugin.h"
#include "qxttreewidgetplugin.h"
#include <QtPlugin>

QList<QDesignerCustomWidgetInterface*> QxtDesignerPlugins::customWidgets() const
{
	QList<QDesignerCustomWidgetInterface*> plugins;
	plugins << new QxtLabelPlugin()
		<< new QxtPushButtonPlugin()
		<< new QxtCheckComboBoxPlugin()
		<< new QxtSpanSliderPlugin()
		<< new QxtStringSpinBoxPlugin()
		<< new QxtGroupBoxPlugin()
		<< new QxtListWidgetPlugin()
		<< new QxtTreeWidgetPlugin()
		<< new QxtTableWidgetPlugin()
		<< new QxtStarsPlugin()
		<< new QxtProgressLabelPlugin();
	return plugins;
}

Q_EXPORT_PLUGIN(QxtDesignerPlugins)
