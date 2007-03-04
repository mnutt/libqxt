/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTSTRINGSPINBOXTASKMENU_H
#define QXTSTRINGSPINBOXTASKMENU_H

#include <QList>
#include <QExtensionFactory>
#include <QDesignerTaskMenuExtension>

class QAction;
class QxtStringSpinBox;

class QxtStringSpinBoxTaskMenu : public QObject, public QDesignerTaskMenuExtension
{
	Q_OBJECT
	Q_INTERFACES(QDesignerTaskMenuExtension)
	
public:
	QxtStringSpinBoxTaskMenu(QxtStringSpinBox* spinBox, const QList<QAction*>& actions, QExtensionManager* manager, QObject* parent);
	
	QAction* preferredEditAction() const;
	QList<QAction*> taskActions() const;
	
private slots:
	void editItems();
	
private:
	QAction* separator;
	QAction* editItemsAction;
	QxtStringSpinBox* spinBox;
	QExtensionManager* manager;
	QList<QAction*> defaultActions;
};

class QxtStringSpinBoxTaskMenuFactory : public QExtensionFactory
{
	Q_OBJECT
	
public:
	QxtStringSpinBoxTaskMenuFactory(QExtensionManager* manager = 0);
	
protected:
	QObject* createExtension(QObject* object, const QString& iid, QObject* parent) const;
	
private:
	void pickDefaultActions(QxtStringSpinBox* spinBox, const QString& iid) const;
	static QList<QAction*> defaultActions;
};

#endif // QXTSTRINGSPINBOXTASKMENU_H
