/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTPUSHBUTTONPLUGIN_H
#define QXTPUSHBUTTONPLUGIN_H

#include <QObject>
#include "QxtDesignerPlugin.h"

class QxtPushButtonPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtPushButtonPlugin(QObject* parent = 0);
	
	QString domXml() const;
	QString includeFile() const;
	QString name() const;
	QWidget* createWidget(QWidget* parent);
};

#endif // QXTPUSHBUTTONPLUGIN_H
