/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTTABWIDGETPLUGIN_H
#define QXTTABWIDGETPLUGIN_H

#include <QObject>
#include <QDesignerTaskMenuExtension>
#include "QxtDesignerPlugin.h"

class QxtTabWidget;

class QxtTabWidgetPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtTabWidgetPlugin(QObject* parent = 0);
	QString domXml() const;
	QString includeFile() const;
	QString name() const;
	QWidget* createWidget(QWidget* parent);
	bool isContainer() const;
	void initialize(QDesignerFormEditorInterface* editor);
};

#endif // QXTTABWIDGETPLUGIN_H
