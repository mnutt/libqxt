/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTSPANSLIDERPLUGIN_H
#define QXTSPANSLIDERPLUGIN_H

#include <QObject>
#include "QxtDesignerPlugin.h"

class QxtSpanSliderPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtSpanSliderPlugin(QObject* parent = 0);
	
	QString domXml() const;
	QString includeFile() const;
	QString name() const;
	QWidget* createWidget(QWidget* parent);
};

#endif // QXTSPANSLIDERPLUGIN_H
