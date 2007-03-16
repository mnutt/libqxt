/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTCHECKCOMBOBOX_H
#define QXTCHECKCOMBOBOX_H

#include <QComboBox>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtPimpl.h>

class QxtCheckComboBoxPrivate;

class QXT_GUI_EXPORT QxtCheckComboBox : public QComboBox
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtCheckComboBox);
	Q_PROPERTY(QString separator READ separator WRITE setSeparator)
	Q_PROPERTY(QString defaultText READ defaultText WRITE setDefaultText)
	Q_PROPERTY(QStringList checkedItems READ checkedItems WRITE setCheckedItems)
	Q_PROPERTY(QxtCheckComboBox::CheckMode checkMode READ checkMode WRITE setCheckMode)
	Q_ENUMS(CheckMode)
	
public:
	enum CheckMode
	{
		CheckIndicator,
		CheckWholeItem
	};
	
	explicit QxtCheckComboBox(QWidget* parent = 0);
	virtual ~QxtCheckComboBox();
	
	QStringList checkedItems() const;
	void setCheckedItems(const QStringList& items);
	
	QString defaultText() const;
	void setDefaultText(const QString& text);
	
	Qt::CheckState itemCheckState(int index) const;
	void setItemCheckState(int index, Qt::CheckState state);
	
	QString separator() const;
	void setSeparator(const QString& separator);
	
	CheckMode checkMode() const;
	void setCheckMode(CheckMode mode);
	
signals:
	void checkedItemsChanged(const QStringList& items);

#ifndef QXT_DOXYGEN_RUN
protected:
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTCHECKCOMBOBOX_H
