/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTTREEWIDGETPLUGIN_H
#define QXTTREEWIDGETPLUGIN_H

#include <QObject>
#include "QxtDesignerPlugin.h"

class QxtTreeWidgetPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtTreeWidgetPlugin(QObject* parent = 0);
	
	QString domXml() const;
	QString includeFile() const;
	QString name() const;
	QWidget* createWidget(QWidget* parent);
};

#endif // QXTTREEWIDGETPLUGIN_H
