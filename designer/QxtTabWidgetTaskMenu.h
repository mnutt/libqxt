/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTTABWIDGETTASKMENU_H
#define QXTTABWIDGETTASKMENU_H

#include <QObject>
#include <QExtensionFactory>
#include <QDesignerTaskMenuExtension>

class QxtTabWidget;

class QxtTabWidgetTaskMenu : public QObject, public QDesignerTaskMenuExtension
{
	Q_OBJECT
	Q_INTERFACES(QDesignerTaskMenuExtension)
	
public:
	QxtTabWidgetTaskMenu(QxtTabWidget* widget, QList<QAction*> actions, QObject* parent);
	QAction* preferredEditAction() const;
	QList<QAction*> taskActions() const;
	
private slots:
	void addPage();
	void delPage();
	
private:
	QAction* addAct;
	QAction* delAct;
	QList<QAction*> defaultActions;
	QxtTabWidget* tabWidget;
};

class QxtTabWidgetTaskMenuFactory : public QExtensionFactory
{
	Q_OBJECT
	
public:
	QxtTabWidgetTaskMenuFactory(QExtensionManager* parent = 0);
	
protected:
	QObject* createExtension(QObject* object, const QString& iid, QObject* parent) const;
};

#endif // QXTTABWIDGETTASKMENU_H
