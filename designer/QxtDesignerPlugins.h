/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTDESIGNERPLUGINS_H
#define QXTDESIGNERPLUGINS_H

#include <QObject>
#include <QDesignerCustomWidgetCollectionInterface>

class QxtDesignerPlugins : public QObject, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
	
public:
	QList<QDesignerCustomWidgetInterface*> customWidgets() const;
};

#endif // QXTDESIGNERPLUGINS_H
