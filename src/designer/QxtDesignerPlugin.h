/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTDESIGNERPLUGIN_H
#define QXTDESIGNERPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class QxtDesignerPlugin : public QDesignerCustomWidgetInterface
{
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	QxtDesignerPlugin();
	
	bool isContainer() const;
	bool isInitialized() const;
	QIcon icon() const;
	QString group() const;
	QString toolTip() const;
	QString whatsThis() const;
	void initialize(QDesignerFormEditorInterface*);
	
private:
	bool init;
};

#endif // QXTDESIGNERPLUGIN_H
