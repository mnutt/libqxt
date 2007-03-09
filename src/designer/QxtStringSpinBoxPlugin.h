/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTSTRINGSPINBOXPLUGIN_H
#define QXTSTRINGSPINBOXPLUGIN_H

#include <QObject>
#include "QxtDesignerPlugin.h"

class QxtStringSpinBoxPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtStringSpinBoxPlugin(QObject* parent = 0);
	
	QString domXml() const;
	QString includeFile() const;
	QString name() const;
	QWidget* createWidget(QWidget* parent);
};

#endif // QXTSTRINGSPINBOXPLUGIN_H
