/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtCheckComboBox.h"
#include "private/QxtCheckComboBox_p.h"
#include <QStyleOptionButton>
#include <QApplication>
#include <QMouseEvent>
#include <QLineEdit>

QxtCheckComboBoxPrivate::QxtCheckComboBoxPrivate()
{
	separator = QLatin1String(",");
}

void QxtCheckComboBoxPrivate::hidePopup()
{
	qxt_p().hidePopup();
}

void QxtCheckComboBoxPrivate::updateCheckedItems()
{
	checkedItems.clear();
	for (int i = 0; i < qxt_p().model()->rowCount(); ++i)
	{
		const QModelIndex& index = qxt_p().model()->index(i, 0);
		const QVariant& data = index.data(Qt::CheckStateRole);
		const Qt::CheckState state = static_cast<Qt::CheckState>(data.toInt());
		if (state == Qt::Checked)
		{
			checkedItems += index.data().toString();
		}
	}
	
	if (checkedItems.count() > 0)
		qxt_p().lineEdit()->setText(checkedItems.join(separator));
	else
		qxt_p().lineEdit()->setText(defaultText);
	
	// TODO: find a way to recalculate a meaningful size hint
}

QxtCheckComboView::QxtCheckComboView(QWidget* parent) : QListView(parent)
{
}

QxtCheckComboView::~QxtCheckComboView()
{
}

bool QxtCheckComboView::eventFilter(QObject* object, QEvent* event)
{
	Q_UNUSED(object);
	if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
		const QModelIndex& index = indexAt(mouse->pos());
		if (index.isValid())
		{
			// check if the mouse was released over the checkbox
			QStyleOptionButton option;
			option.QStyleOption::operator=(viewOptions());
			option.rect = visualRect(index);
			const QRect& rect = style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &option);
			if (rect.contains(mouse->pos()))
			{
				// mouse was released over the check indicator,
				// bypass combobox and deliver the event just for the listview
				QListView::mouseReleaseEvent(mouse);
			}
			else
			{
				// it's ok to close
				emit hideRequested();
			}
			return true;
		}
	}
	return false;
}

QxtCheckComboModel::QxtCheckComboModel(QObject* parent)
	: QStandardItemModel(0, 1, parent) // rows,cols
{
}

QxtCheckComboModel::~QxtCheckComboModel()
{
}

Qt::ItemFlags QxtCheckComboModel::flags(const QModelIndex& index) const
{
	return QStandardItemModel::flags(index) | Qt::ItemIsUserCheckable;
}

bool QxtCheckComboModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	bool ok = QStandardItemModel::setData(index, value, role);
	if (ok && role == Qt::CheckStateRole)
	{
		emit checkStateChanged();
	}
	return ok;
}

bool QxtCheckComboModel::setItemData(const QModelIndex& index, const QMap<int, QVariant>& roles)
{
	// workaround: rely on this that a new item was added
	// because QComboBox::insertItem() is such a biatch
	QMap<int, QVariant> copy = roles;
	copy.insert(Qt::CheckStateRole, Qt::Unchecked);
	bool ok = QStandardItemModel::setItemData(index, copy);
	if (ok)
	{
		emit checkStateChanged();
	}
	return ok;
}

QxtCheckComboBox::QxtCheckComboBox(QWidget* parent) : QComboBox(parent)
{
	QXT_INIT_PRIVATE(QxtCheckComboBox);
	QxtCheckComboModel* model = new QxtCheckComboModel(this);
	QxtCheckComboView*  view  = new QxtCheckComboView(this);
	setModel(model);
	setView(view);
	
	// these 2 lines below are important and must be
	// applied AFTER QComboBox::setView() because
	// QComboBox installs it's own filter on the view
	view->installEventFilter(view);			// <--- !!!
	view->viewport()->installEventFilter(view);	// <--- !!!
	
	// read-only contents
	QLineEdit* lineEdit = new QLineEdit(this);
	lineEdit->setReadOnly(true);
	setLineEdit(lineEdit);
	
	connect(view, SIGNAL(hideRequested()), &qxt_d(), SLOT(hidePopup()));
	connect(model, SIGNAL(checkStateChanged()), &qxt_d(), SLOT(updateCheckedItems()));
}

QxtCheckComboBox::~QxtCheckComboBox()
{
}

Qt::CheckState QxtCheckComboBox::itemCheckState(int index) const
{
	return static_cast<Qt::CheckState>(itemData(index, Qt::CheckStateRole).toInt());
}

void QxtCheckComboBox::setItemCheckState(int index, Qt::CheckState state)
{
	setItemData(index, state, Qt::CheckStateRole);
}

QStringList QxtCheckComboBox::checkedItems() const
{
	return qxt_d().checkedItems;
}

void QxtCheckComboBox::setCheckedItems(const QStringList& items)
{
	// not the most efficient solution but most likely nobody
	// will put too many items into a combo box anyway so...
	foreach (const QString& text, items)
	{
		const int index = findText(text);
		setItemCheckState(index, index != -1 ? Qt::Checked : Qt::Unchecked);
	}
}

QString QxtCheckComboBox::defaultText() const
{
	return qxt_d().defaultText;
}

void QxtCheckComboBox::setDefaultText(const QString& text)
{
	qxt_d().defaultText = text;
}

QString QxtCheckComboBox::separator() const
{
	return qxt_d().separator;
}

void QxtCheckComboBox::setSeparator(const QString& separator)
{
	qxt_d().separator = separator;
}

void QxtCheckComboBox::keyPressEvent(QKeyEvent* event)
{
	if (event->key() != Qt::Key_Up && event->key() != Qt::Key_Down)
	{
		QComboBox::keyPressEvent(event);
	}
}

void QxtCheckComboBox::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() != Qt::Key_Up && event->key() != Qt::Key_Down)
	{
		QComboBox::keyReleaseEvent(event);
	}
}
