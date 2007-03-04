/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTSTRINGLISTEDITOR_H
#define QXTSTRINGLISTEDITOR_H

#include <QDialog>
#include <QModelIndex>
#include <QStringList>

class QListView;
class QLineEdit;
class QButtonGroup;
class QStringListModel;

class QxtStringListEditor : public QDialog
{
	Q_OBJECT
	
public:
	explicit QxtStringListEditor(QWidget* parent = 0);
	~QxtStringListEditor();
	
	QStringList stringList() const;
	void setStringList(const QStringList& strings);
	
private slots:
	void moveUp();
	void moveDown();
	void add();
	void remove();
	void applyText(const QString& text);
	void applyIndex(const QModelIndex& index = QModelIndex());
	void updateUi();
	
private:
	int currentIndex() const;
	void setCurrentIndex(int index);
	int count() const;
	QString stringAt(int index) const;
	void setStringAt(int index, const QString &value);
	void removeString(int index);
	void insertString(int index, const QString &value);
	void editString(int index);
	void moveString(int from, int to);
	
	QListView* view;
	QLineEdit* value;
	QButtonGroup* buttons;
	QStringListModel* model;
};

#endif // QXTSTRINGLISTEDITOR_H
