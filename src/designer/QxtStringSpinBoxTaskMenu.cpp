/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include <QtDesigner>
#include <QtGui>

#include "QxtStringSpinBox.h"
#include "QxtStringSpinBoxTaskMenu.h"
#include "QxtStringListEditor.h"

QxtStringSpinBoxTaskMenu::QxtStringSpinBoxTaskMenu(QxtStringSpinBox* spinBox, const QList<QAction*>& actions, QExtensionManager* manager, QObject* parent)
	: QObject(parent), spinBox(spinBox), manager(manager), defaultActions(actions)
{
	separator = new QAction(this);
	separator->setSeparator(true);
	editItemsAction = new QAction(tr("Edit Items..."), this);
	connect(editItemsAction, SIGNAL(triggered()), this, SLOT(editItems()));
}

#include <QtDebug>
void QxtStringSpinBoxTaskMenu::editItems()
{
	QDesignerPropertySheetExtension* propertySheet  = 0;
	propertySheet = qt_extension<QDesignerPropertySheetExtension*>(manager, spinBox);
	int index = propertySheet->indexOf(QLatin1String("strings"));
	
	qDebug() << index;
	
	QxtStringListEditor editor;
	editor.setStringList(propertySheet->property(index).toStringList());
	if (editor.exec() == QDialog::Accepted)
	{
		propertySheet->setProperty(index, editor.stringList());
		propertySheet->setChanged(index, true);
	}
	delete propertySheet;
}

QAction* QxtStringSpinBoxTaskMenu::preferredEditAction() const
{
	return editItemsAction;
}

 QList<QAction*> QxtStringSpinBoxTaskMenu::taskActions() const
{
	QList<QAction*> list;
	list += editItemsAction;
	list += separator;
	list += defaultActions;
	return list;
}

QxtStringSpinBoxTaskMenuFactory::QxtStringSpinBoxTaskMenuFactory(QExtensionManager* manager)
	: QExtensionFactory(manager)
{
}

QObject* QxtStringSpinBoxTaskMenuFactory::createExtension(QObject* object, const QString& iid, QObject* parent) const
{
	if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
		return 0;
	
	if (QxtStringSpinBox* spinBox = qobject_cast<QxtStringSpinBox*>(object))
	{
		if (defaultActions.isEmpty())
		{
			pickDefaultActions(spinBox, iid);
		}
		return new QxtStringSpinBoxTaskMenu(spinBox, defaultActions, qobject_cast<QExtensionManager*>(QObject::parent()), parent);
	}
	
	return 0;
}

void QxtStringSpinBoxTaskMenuFactory::pickDefaultActions(QxtStringSpinBox* spinBox, const QString& iid) const
{
	QExtensionManager* manager = qobject_cast<QExtensionManager*>(parent());
	if (manager)
	{
		QxtStringSpinBoxTaskMenuFactory* factory = const_cast<QxtStringSpinBoxTaskMenuFactory*>(this);
		manager->unregisterExtensions(factory, iid);
		QObject* object = manager->extension(spinBox, iid);
		if (object && object->metaObject()->className() == QLatin1String("qdesigner_internal::QDesignerTaskMenu"))
		{
			QDesignerTaskMenuExtension* extension = qobject_cast<QDesignerTaskMenuExtension*>(object);
			if (extension)
			{
				defaultActions = extension->taskActions();
			}
		}
		manager->registerExtensions(factory, iid);
	}
}

QList<QAction*> QxtStringSpinBoxTaskMenuFactory::defaultActions;
