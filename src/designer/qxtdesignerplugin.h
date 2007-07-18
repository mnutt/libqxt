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
#ifndef QXTDESIGNERPLUGIN_H
#define QXTDESIGNERPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class QxtDesignerPlugin : public QDesignerCustomWidgetInterface
{
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	QxtDesignerPlugin(const QString& plugin);
	
	QString group() const;
	QIcon icon() const;
	QString includeFile () const;
	void initialize(QDesignerFormEditorInterface*);
	bool isContainer() const;
	bool isInitialized() const;
	QString name() const;
	QString toolTip() const;
	QString whatsThis() const;
	
private:
	bool init;
	QString plugin;
};

#endif // QXTDESIGNERPLUGIN_H
