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
#include "qxtstringspinbox.h"
#include "qxtstringspinboxplugin.h"
#include <QtDesigner>
#include <QtPlugin>

QxtStringSpinBoxPlugin::QxtStringSpinBoxPlugin(QObject* parent)
	: QObject(parent), QxtDesignerPlugin("QxtStringSpinBox")
{
}

QWidget* QxtStringSpinBoxPlugin::createWidget(QWidget* parent)
{
	return new QxtStringSpinBox(parent);
}

QString QxtStringSpinBoxPlugin::domXml() const
{
	return "<widget class=\"QxtStringSpinBox\" name=\"qxtStringSpinBox\" />";
}
