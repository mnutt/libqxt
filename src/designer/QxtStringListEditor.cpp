/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtStringListEditor.h"
#include <QtGui>

enum StringButtons
{
	ButtonUp, ButtonDown, ButtonAdd, ButtonRemove
};

QxtStringListEditor::QxtStringListEditor(QWidget* parent) : QDialog(parent)
{
	setWindowTitle(tr("Edit StringList"));
	QGroupBox* group = new QGroupBox("StringList", this);
	QGridLayout* grid = new QGridLayout(group);
	
	view = new QListView(group);
	model = new QStringListModel(view);
	view->setModel(model);
	connect(view->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
		this, SLOT(applyIndex(const QModelIndex&)));
	connect(view->itemDelegate(), SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)),
		this, SLOT(applyIndex()));
	grid->addWidget(view, 0, 0);
	
	QToolButton* up = new QToolButton(group);
	up->setArrowType(Qt::UpArrow);
	connect(up, SIGNAL(clicked()), this, SLOT(moveUp()));
	QToolButton* down = new QToolButton(group);
	down->setArrowType(Qt::DownArrow);
	connect(down, SIGNAL(clicked()), this, SLOT(moveDown()));
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addStretch();
	vbox->addWidget(up);
	vbox->addWidget(down);
	vbox->addStretch();
	grid->addLayout(vbox, 0, 1);
	
	QToolButton* add = new QToolButton(group);
	add->setText(tr("New"));
	connect(add, SIGNAL(clicked()), this, SLOT(add()));
	QToolButton* remove = new QToolButton(group);
	remove->setText(tr("Delete"));
	connect(remove, SIGNAL(clicked()), this, SLOT(remove()));
	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(add);
	hbox->addWidget(remove);
	hbox->addStretch();
	grid->addLayout(hbox, 1, 0, 1, 2);
	
	value = new QLineEdit(group);
	connect(value, SIGNAL(textChanged(const QString&)), this, SLOT(applyText(const QString&)));
	QLabel* label = new QLabel(tr("&Value:"), group);
	label->setBuddy(value);
	hbox = new QHBoxLayout;
	hbox->addWidget(label);
	hbox->addWidget(value);
	grid->addLayout(hbox, 2, 0, 1, 2);
	
	QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
	connect(box, SIGNAL(accepted()), this, SLOT(accept()));
	connect(box, SIGNAL(rejected()), this, SLOT(reject()));
	
	vbox = new QVBoxLayout(this);
	vbox->addWidget(group);
	vbox->addWidget(box);
	
	buttons = new QButtonGroup(this);
	buttons->addButton(up, ButtonUp);
	buttons->addButton(down, ButtonDown);
	buttons->addButton(add, ButtonAdd);
	buttons->addButton(remove, ButtonRemove);
	updateUi();
}

QxtStringListEditor::~QxtStringListEditor()
{
}

QStringList QxtStringListEditor::stringList() const
{
	return model->stringList();
}

void QxtStringListEditor::setStringList(const QStringList& strings)
{
	model->setStringList(strings);
	updateUi();
}

void QxtStringListEditor::moveUp()
{
	int from = currentIndex();
	int to = from - 1;
	moveString(from, to);
	updateUi();
}

void QxtStringListEditor::moveDown()
{
	int from = currentIndex();
	int to = from + 1;
	moveString(from, to);
	updateUi();
}

void QxtStringListEditor::add()
{
	int to = currentIndex();
	if (to == -1)
		to = count() - 1;
	++to;
	insertString(to, QString());
	setCurrentIndex(to);
	updateUi();
	editString(to);
}

void QxtStringListEditor::remove()
{
	removeString(currentIndex());
	setCurrentIndex(currentIndex());
	updateUi();
}

void QxtStringListEditor::applyText(const QString& text)
{
	setStringAt(currentIndex(), text);
}

void QxtStringListEditor::updateUi()
{
	int index = currentIndex();
	int amount = count();
	buttons->button(ButtonUp)->setEnabled((amount > 1) && (index > 0));
	buttons->button(ButtonDown)->setEnabled((amount > 1) && (index >= 0) && (index < (amount - 1)));
	buttons->button(ButtonRemove)->setEnabled(index != -1);
	value->setEnabled(index != -1);
}

int QxtStringListEditor::currentIndex() const
{
	return view->currentIndex().row();
}

void QxtStringListEditor::setCurrentIndex(int index)
{
	QModelIndex modelIndex = model->index(index, 0);
	if (view->currentIndex() != modelIndex)
		view->setCurrentIndex(modelIndex);
	value->setText(stringAt(index));
}

int QxtStringListEditor::count() const
{
	return model->rowCount();
}

QString QxtStringListEditor::stringAt(int index) const
{
	return model->data(model->index(index, 0), Qt::DisplayRole).toString();
}

void QxtStringListEditor::setStringAt(int index, const QString& value)
{
	model->setData(model->index(index, 0), value);
}

void QxtStringListEditor::removeString(int index)
{
	model->removeRow(index);
}

void QxtStringListEditor::insertString(int index, const QString &value)
{
	model->insertRow(index);
	model->setData(model->index(index, 0), value);
}

void QxtStringListEditor::editString(int index)
{
	view->edit(model->index(index, 0));
}

void QxtStringListEditor::moveString(int from, int to)
{
	QString value = stringAt(from);
	removeString(from);
	insertString(to, value);
	setCurrentIndex(to);
}

void QxtStringListEditor::applyIndex(const QModelIndex& index)
{
	setCurrentIndex(index.isValid() ? index.row() : currentIndex());
	updateUi();
}
