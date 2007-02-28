/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTLABELPLUGIN_H
#define QXTLABELPLUGIN_H

#include <QObject>
#include "QxtDesignerPlugin.h"

class QxtLabelPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtLabelPlugin(QObject* parent = 0);
	
	QString domXml() const;
	QString includeFile() const;
	QString name() const;
	QWidget* createWidget(QWidget* parent);
};

#endif // QXTLABELPLUGIN_H
