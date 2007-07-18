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
#include "qxtdesignerplugin.h"

QxtDesignerPlugin::QxtDesignerPlugin(const QString& plugin) : init(false), plugin(plugin)
{
}

QString QxtDesignerPlugin::group() const
{
	return "QxtGui Widgets";
}

QIcon QxtDesignerPlugin::icon() const
{
	return QIcon(":/logo.png");
}

QString QxtDesignerPlugin::includeFile() const
{
	return plugin;
}

void QxtDesignerPlugin::initialize(QDesignerFormEditorInterface*)
{
	if (init) return;
	init = true;
}

bool QxtDesignerPlugin::isContainer() const
{
	return false;
}

bool QxtDesignerPlugin::isInitialized() const
{
	return init;
}

QString QxtDesignerPlugin::name() const
{
	return plugin;
}

QString QxtDesignerPlugin::toolTip() const
{
	return plugin;
}

QString QxtDesignerPlugin::whatsThis() const
{
	return plugin;
}
