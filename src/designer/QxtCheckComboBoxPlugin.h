/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTCHECKCOMBOBOXPLUGIN_H
#define QXTCHECKCOMBOBOXPLUGIN_H

#include <QObject>
#include "QxtDesignerPlugin.h"

class QxtCheckComboBoxPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtCheckComboBoxPlugin(QObject* parent = 0);
	
	QString domXml() const;
	QString includeFile() const;
	QString name() const;
	QWidget* createWidget(QWidget* parent);
};

#endif // QXTCHECKCOMBOBOXPLUGIN_H
