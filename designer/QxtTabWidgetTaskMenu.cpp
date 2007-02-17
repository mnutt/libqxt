/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTabWidget.h"
#include "QxtTabWidgetTaskMenu.h"
#include <QExtensionManager>
#include <QAction>

QxtTabWidgetTaskMenu::QxtTabWidgetTaskMenu(QxtTabWidget* widget, QList<QAction*> actions, QObject* parent)
	: QObject(parent), defaultActions(actions), tabWidget(widget)
{
	addAct = new QAction(tr("Add page"), widget);
	delAct = new QAction(tr("Delete page"), widget);
	connect(addAct, SIGNAL(triggered()), this, SLOT(addPage()));
	connect(delAct, SIGNAL(triggered()), this, SLOT(delPage()));
}

QAction* QxtTabWidgetTaskMenu::preferredEditAction() const
{
	return addAct;
}

QList<QAction*> QxtTabWidgetTaskMenu::taskActions() const
{
	QAction* separator = new QAction(addAct);
	separator->setSeparator(true);
	return QList<QAction*>() << defaultActions << separator << addAct << delAct;
}

void QxtTabWidgetTaskMenu::addPage()
{
	tabWidget->addTab(new QWidget(tabWidget), tr("Tab %1").arg(tabWidget->count() + 1));
	delAct->setEnabled(tabWidget->count());
}

void QxtTabWidgetTaskMenu::delPage()
{
	tabWidget->removeTab(tabWidget->currentIndex());
	delAct->setEnabled(tabWidget->count());
}

QxtTabWidgetTaskMenuFactory::QxtTabWidgetTaskMenuFactory(QExtensionManager* parent)
	: QExtensionFactory(parent)
{
}

QObject* QxtTabWidgetTaskMenuFactory::createExtension(QObject* object, const QString& iid, QObject* parent) const
{
	if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
		return 0;

	if (QxtTabWidget* tabWidget = qobject_cast<QxtTabWidget*>(object))
	{
		// a workaround to get the default task menu actions
		static QList<QAction*> defaultActions;
		if (defaultActions.isEmpty())
		{
			QExtensionManager* manager = static_cast<QExtensionManager*>(QObject::parent());
			manager->unregisterExtensions(const_cast<QxtTabWidgetTaskMenuFactory*>(this), iid);
			QObject* defaultObject = manager->extension(object, iid);
			QDesignerTaskMenuExtension* defaultExtension = qobject_cast<QDesignerTaskMenuExtension*>(defaultObject);
			if (defaultExtension && defaultObject->metaObject()->className() == QString("qdesigner_internal::QDesignerTaskMenu"))
				defaultActions = defaultExtension->taskActions();
			manager->registerExtensions(const_cast<QxtTabWidgetTaskMenuFactory*>(this), iid);
		}
		return new QxtTabWidgetTaskMenu(tabWidget, defaultActions, parent);
	}
	
	return 0;
}
