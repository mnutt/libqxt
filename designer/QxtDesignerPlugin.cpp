/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtDesignerPlugin.h"

QxtDesignerPlugin::QxtDesignerPlugin() : init(false)
{
}

bool QxtDesignerPlugin::isContainer() const
{
	return false;
}

bool QxtDesignerPlugin::isInitialized() const
{
	return init;
}

QIcon QxtDesignerPlugin::icon() const
{
	return QIcon(":/logo.png");
}

QString QxtDesignerPlugin::group() const
{
	return "Qxt Widgets";
}

QString QxtDesignerPlugin::toolTip() const
{
	return QString();
}

QString QxtDesignerPlugin::whatsThis() const
{
	return QString();
}

void QxtDesignerPlugin::initialize(QDesignerFormEditorInterface*)
{
	if (init) return;
	init = true;
}
