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
#include "qxtstars.h"
#include "qxtstarsplugin.h"
#include <QtPlugin>

QxtStarsPlugin::QxtStarsPlugin(QObject* parent)
	: QObject(parent), QxtDesignerPlugin("QxtStars")
{
}

QWidget* QxtStarsPlugin::createWidget(QWidget* parent)
{
	return new QxtStars(parent);
}

QString QxtStarsPlugin::domXml() const
{
	return "<widget class=\"QxtStars\" name=\"qxtStars\">\n"
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
